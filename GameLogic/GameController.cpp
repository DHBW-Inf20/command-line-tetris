#include <thread>
#include "GameController.h"
#include "../UI/Config.h"
#include "../UI/DataClasses/Blocks/BlueRicky.h"
#include "../UI/DataClasses/Blocks/CleverlandZ.h"
#include "../UI/DataClasses/Blocks/Hero.h"
#include "../UI/DataClasses/Blocks/OrangeRicky.h"
#include "../UI/DataClasses/Blocks/RhodeIslandZ.h"
#include "../UI/DataClasses/Blocks/Smashboy.h"
#include "../UI/DataClasses/Blocks/Teewee.h"
#include "../Utilities/Logger.h"
#include "../Utilities/MemoryLeakDetection.h"

/* Versucht die 4x4-Matrix des aktuellen Blockes in das richtige Feld einzusetzen */
bool GameController::TryInsertCurrentBlockInField()
{  
    auto tetrisBlockMatrixOld = CurrentBlockLastUpdate->BuildMatrix();
    auto tetrisBlockMatrix = CurrentBlock->BuildMatrix();
    for (auto i = 0; i < rowCount; i++)
    {
        for (auto j = 0; j < columnCount; j++)
        {
            if (tetrisBlockMatrixOld[i][j] != nullptr)
            {
                if (i != 0 && i != rowCount - 1 && j != 0 && j != columnCount - 1) // Rand außen vor lassen
                {            
                    Field[i][j] = nullptr;                                         // Alte Position vom TetrisBock löschen                   
                }
            }
            auto* const tetrisBlockTile = tetrisBlockMatrix[i][j];
            auto* const matrixBlockTile = Field[i][j];
            if (tetrisBlockTile != nullptr && matrixBlockTile == nullptr) // Feld wird gesetzt
            {
                Field[i][j] = tetrisBlockTile;
            }
            else if (tetrisBlockTile != nullptr && matrixBlockTile != nullptr)
            {
                // Warum geht das nicht amk?
                printf("Stop");
                Finish();               
            }
        }
    }
    delete CurrentBlockLastUpdate;
    CurrentBlockLastUpdate = CurrentBlock->Clone(); 
    return true;
}

/* Sorgt dafür, dass alle Blöcke ausgeglichen gespawnt werden, wird von createBlock aufgerufen */
bool GameController::IsSpawningBalanced(const int number)
{
	const auto sum = BlocksSpawned[0] + BlocksSpawned[1] + BlocksSpawned[2] + BlocksSpawned[3] + BlocksSpawned[4] + BlocksSpawned[5] + BlocksSpawned[6];
	const auto avg = sum / 7;
    if (BlocksSpawned[number] > avg)
    {
        return false;
    }
    return true;
}

/* Spawnt einen der sieben Blöcke */
void GameController::CreateBlock()
{
	auto num = GetRandomNumberBetween(0, 6);
    while (!IsSpawningBalanced(num))
    {
        num = GetRandomNumberBetween(0, 6);
    }
    
    delete CurrentBlock;

    switch (num)
    {
    case 0:
        CurrentBlock = new BlueRicky();
        BlocksSpawned[0]++;
        break;
    case 1:
        CurrentBlock = new CleverlandZ();
        BlocksSpawned[1]++;
        break;
    case 2:
        CurrentBlock = new Hero();
        BlocksSpawned[2]++;
        break;
    case 3:
        CurrentBlock = new OrangeRicky();
        BlocksSpawned[3]++;
        break;
    case 4:
        CurrentBlock = new RhodeIslandZ();
        BlocksSpawned[4]++;
        break;
    case 5:
        CurrentBlock = new Smashboy();
        BlocksSpawned[5]++;
        break;
    case 6:
        CurrentBlock = new Teewee();
        BlocksSpawned[6]++;
        break;
    default:    
        break;;
    }

    auto matrix = CurrentBlock->BuildMatrix();
    for (auto i = 0; i < rowCount; i++)
    {
        for (auto j = 0; j < columnCount; j++)
        {
            if(Field[i][j]!=nullptr&&matrix[i][j]!=nullptr)
            {
                Finish();
                return;
            }
        }
    }

    delete CurrentBlockLastUpdate;
    CurrentBlockLastUpdate = CurrentBlock->Clone();
}

/* Wird beim drücken der Taste B aufgerufen und pausiert das Spiel */
void GameController::BKeyPressed()
{
    GameRunning = false;
    printf("b pressed\n");
}

/* Löscht die übergebene Reihe und verschiebt die Reihen darüber jeweils nach unten */
void GameController::DeleteRow(const int row)
{

	for(size_t i=1; i<columnCount-1;i++)
	{
		delete Field[row][i];
        Field[row][i] = nullptr;
	}
	
    for (size_t j = row; j > 0; j--)
    {
        for (auto i = 1; i < columnCount - 1; i++)
        {        	
            if (j == 1)
            {               
                Field[1][i] = nullptr;              
            }
            else
            {
                if (Field[j - 1][i] == nullptr)
                    Field[j][i] = nullptr;
                else
					Field[j][i] = Field[j - 1][i];
            }
        }
    }
}

/* Prüft ob eine oder mehrere Reihen voll sind und löscht diese gegebenenfalls. Daraufhin werden Punkte gutgeschrieben und ggf. das Level erhöht.*/
void GameController::CheckRows()
{
    if (CanDelete)
    {
	    auto rowsDeleted = 0;
        for (auto i = 1; i < rowCount - 1; i++)
        {
	        auto matches = 0;
            for (auto j = 0; j < columnCount; j++)
            {
                if (Field[i][j] != nullptr)
                    matches++;
            }
            if (matches == columnCount)
            {
                DeleteRow(i);
                rowsDeleted++;
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
            }
        }
        CanDelete = false;
        
        switch (rowsDeleted) // Add Score
        {
        case 1:
            Score = Score + (40+(40*Level));
            break;
        case 2:
            Score = Score + (100+(100*Level));
            break;
        case 3:
            Score = Score + (300+(300*Level));
            break;
        case 4:
            Score = Score + (1200+(1200*Level));
            break;
        default: // = 0 lines cleared
            break;
        }

        RowsCleared = RowsCleared + rowsDeleted;
        if(RowsCleared >= 10 && Level < 10)
        {
            Level++;
            RowsCleared = RowsCleared - 10;
        }
    }
}

/* Pfeil nach Rechts oder D wurde gedrückt, versucht den Block nach Rechts zu schieben */
void GameController::RightKeyPressed() const
{
    MainLock.lock();
    if (CheckCanMove(CurrentBlock, 'r'))
        CurrentBlock->TryMoveRight();
    MainLock.unlock();
}

/* Pfeil nach Links oder A wurde gedrückt, versucht den Block nach Links zu schieben */
void GameController::LeftKeyPressed() const
{
    MainLock.lock();
    if (CheckCanMove(CurrentBlock, 'l'))
        CurrentBlock->TryMoveLeft();
    MainLock.unlock();
}

/* Pfeil nach Oben oder W wurde gedrückt, versucht den Block um 90° nach Rechts zu drehen */
void GameController::UpKeyPressed() const
{
    MainLock.lock();
    if (CheckCanMove(CurrentBlock, 't'))
        CurrentBlock->TryRotateRight();
    MainLock.unlock();
}

/* Pfeil nach Unten oder S wurde gedrückt, versucht den Block nach Unten zu verschieben */
void GameController::DownKeyPressed() const
{
    MainLock.lock();
    if (CheckCanMove(CurrentBlock, 'd'))
        CurrentBlock->TryMoveDown();
    MainLock.unlock();
}

/* Leertaste wurde gedrückt, versucht den Block weitest möglich nach unten zu verschieben */
void GameController::SpaceKeyPressed() const
{
    MainLock.lock();
    auto* tileCopy = CurrentBlock->Clone();
    while(CheckCanMove(tileCopy, 'd'))
    {  
        CurrentBlock->TryMoveDown();
        tileCopy->TryMoveDown();
    }
    delete tileCopy;
    MainLock.unlock();
}

GameController::GameController()
{
	Field = Create2DArray<Tile*>(rowCount, columnCount); // [Reihe][Spalte]
	MoveDownLimiter = 0;
	for (auto i = 0; i < 7; i++)
	{
		BlocksSpawned[i] = 0;
	}
}

bool GameController::IsGameRunning() const
{
    return GameRunning;
}

/* Wird in festen Intervallen aufgerufen und zeichnet das aktuelle Feld, prüft ob ein neuer Block erzeugt werden muss und ob eine Reihe voll ist */
void GameController::Update()
{   
	
    MainLock.lock();
    if (TryInsertCurrentBlockInField())
        Ui.Draw(Field, Score, Level);

    if (MoveDownLimiter == WaitingTime[Level])
    {
        if (CheckCanMove(CurrentBlock, 'd'))
        {
            CurrentBlock->TryMoveDown();
        }
        else
        {
            CanDelete = true; // Reihe darf gelöscht werden
            CreateBlock();    // Am Boden
        }
        MoveDownLimiter = 0;
    }
    CheckRows();
    MoveDownLimiter++;
    MainLock.unlock();
}

/* Simuliert mit einer Kopie, ob ein Zug ausgeführt werden kann */
bool GameController::CheckCanMove(TetrisBlock *block, const char direction) const
{
	auto* tileCopy = block->Clone();
    auto fieldCopy = Field;
	
    bool noBorder;
    switch (direction)
    {
    case 'l': // left
        noBorder = tileCopy->TryMoveLeft();
        break;
    case 'r': // right
        noBorder = tileCopy->TryMoveRight();
        break;
    case 'd': // down
        noBorder = tileCopy->TryMoveDown();
        break;
    case 't':
        noBorder = tileCopy->TryRotateRight();
        break;
    default:
        return false;
    }
    if (!noBorder) // Block am Rand -> kein Verschieben möglich
    {      
        return false;
    }

    auto tetrisBlockMatrix = tileCopy->BuildMatrix();
    auto tetirsBlockMatrixOld = CurrentBlockLastUpdate->BuildMatrix();

    int success = true;
    for (auto i = 0; i < rowCount; i++)
    {
        for (auto j = 0; j < columnCount; j++)
        {
            if (tetirsBlockMatrixOld[i][j] != nullptr)
            {
                if (i != 0 && i != rowCount - 1 && j != 0 && j != columnCount - 1) // Rand außen vor lassen
                    fieldCopy[i][j] = nullptr;                                     // Alte Position vom TetrisBock löschen
            }

            auto* const tetrisBlockTile = tetrisBlockMatrix[i][j];
            auto* const matrixBlockTile = fieldCopy[i][j];

            if (tetrisBlockTile != nullptr && matrixBlockTile != nullptr) // Verboten (Position ist nicht frei)
            {
                success = false;
                break;
            }
        }           
    }
	
    delete tileCopy;
    return success;
}

/* Initalisierung und Start des Spieles */
void GameController::Start()
{
    GameRunning = true;
    CanDelete = false;
    Ui.Init(Field);
    CreateBlock();
    Level = 0;
    Score = 0;
    RowsCleared = 0;
}

void GameController::Finish()
{
    GameRunning = false;
}

void GameController::Stop()
{
    Ui.Clear();
}

int GameController::GetScore() const
{
    return Score;
}

int GameController::GetLevel() const
{
    return Level;
}

GameController::~GameController()
{
    delete CurrentBlockLastUpdate;
    delete CurrentBlock;
	for (auto& i : Field)
	{
		for (auto& j : i)
		{
            delete j; //Da jedes Tile irgendwann im Field auftaucht, reicht es aus, am Ende lediglich das gesamte Field zu löschen
		}
	}
}