
#ifndef _tetrisblock_
#define _tetrisblock_
#include "../UI/DataClasses/TetrisBlock.cpp"
#endif

#include <chrono>
#include <thread>
#include <atomic>


#ifndef _config_
#define _config_
#include "..UI/Config.cpp"
#endif

#ifndef _blocks_
#define _blocks_
#include "../UI/DataClasses/Blocks/CleverlandZ.cpp"
#include "../UI/DataClasses/Blocks/BlueRicky.cpp"
#include "../UI/DataClasses/Blocks/Hero.cpp"
#include "../UI/DataClasses/Blocks/OrangeRicky.cpp"
#include "../UI/DataClasses/Blocks/RhodeIslandZ.cpp"
#include "../UI/DataClasses/Blocks/Smashboy.cpp"
#include "../UI/DataClasses/Blocks/Teewee.cpp"
#endif

#include "../UI/UI.cpp"

class GameController
{
private:
    std::atomic<bool> gameRunning = false;
    TetrisBlock *currentBlock;
    TetrisBlock *currentBlockLastUpdate; // Hier wird der Block vom letzten Update gespeichert -> So kann bei einer Änderung das Spielfeld rekonstruiert werden
    std::vector<std::vector<Tile *>> field;
    UI ui;
    float blocksSpawned[7];
    bool tryInsertCurrentBlockInField();
    void createBlock();
    bool checkCanMove(TetrisBlock *block, char direction);
    void checkRows();
    void deleteRow(int row);
    int moveDownLimiter;
    bool isSpawningBalanced(int number);

public:
    GameController();
    bool isGameRunning();
    void update();
    void start();
    void finish();
    void bKeyPressed();
    void dKeyPressed();
    void aKeyPressed();
    void wKeyPressed();
    void sKeyPressed();

    ~GameController();
};

bool GameController::tryInsertCurrentBlockInField()
{
    auto backup = field;
    auto tetirsBlockMatrixOld = currentBlockLastUpdate->buildMatrix();
    auto tetrisBlockMatrix = currentBlock->buildMatrix();
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            if (tetirsBlockMatrixOld[i][j] != nullptr)
            {
                if (i != 0 && i != rowCount - 1 && j != 0 && j != columnCount - 1) // Rand außen vor lassen
                    field[i][j] = nullptr;                                         // Alte Position vom TetrisBock löschen
            }
            auto tetrisBlockTile = tetrisBlockMatrix[i][j];
            auto matrixBlockTile = field[i][j];
            if (tetrisBlockTile != nullptr && matrixBlockTile == nullptr) // Feld wird gesetzt
            {
                field[i][j] = tetrisBlockTile;
            }
        }
    }

    currentBlockLastUpdate = new TetrisBlock(*currentBlock); // TODO: Alte Löschen?
    return true;
}

bool GameController::isSpawningBalanced(int number)
{
    float sum = blocksSpawned[0] + blocksSpawned[1] + blocksSpawned[2] + blocksSpawned[3] + blocksSpawned[4] + blocksSpawned[5] + blocksSpawned[6];
    float avg = sum/7;
    if(blocksSpawned[number] > avg)
    {
        return false;
    }
    return true;
}

void GameController::createBlock()
{
    int num = GetRandomNumberBetween(0, 6);
    while(!isSpawningBalanced(num))
    {
        num = GetRandomNumberBetween(0, 6);
    }

    switch (num) 
    {
    case 0:
        currentBlock = new BlueRicky();
        blocksSpawned[0]++;
        break;
    case 1:
        currentBlock = new CleverlandZ();
        blocksSpawned[1]++;
        break;
    case 2:
        currentBlock = new Hero();
        blocksSpawned[2]++;
        break;
    case 3:
        currentBlock = new OrangeRicky();
        blocksSpawned[3]++;
        break;
    case 4:
        currentBlock = new RhodeIslandZ();
        blocksSpawned[4]++;
        break;
    case 5:
        currentBlock = new Smashboy();
        blocksSpawned[5]++;
        break;
    case 6:
        currentBlock = new Teewee();
        blocksSpawned[6]++;
        break;
    }
    currentBlockLastUpdate = currentBlock;
}

void GameController::bKeyPressed()
{
    gameRunning = false;
    printf("b pressed\n");
}

void GameController::deleteRow(int row)
{
    for (int j = row; j > 0; j--)
    {
        for (int i = 1; i < columnCount - 1; i++)
        {
            if (j == 1)
            {
                field[1][i] = nullptr;
            }
            else
            {
                field[j][i] = field[j - 1][i];
            }
        }
    }
}

void GameController::checkRows()
{
    for (int i = 1; i < rowCount - 1; i++)
    {
        int matches = 0;
        for (int j = 0; j < columnCount; j++)
        {
            if (field[i][j] != nullptr)
                matches++;
        }
        if (matches == columnCount)
        {
            deleteRow(i);   
            std::this_thread::sleep_for(std::chrono::milliseconds(150));        
        }
    }
}

void GameController::dKeyPressed()
{
    if(checkCanMove(currentBlock, 'r'))
        currentBlock->tryMoveRight();
}

void GameController::aKeyPressed()
{
    if(checkCanMove(currentBlock, 'l'))
        currentBlock->tryMoveLeft();
}

void GameController::wKeyPressed()
{
        // Gleich wie Left/Right/Down -> davor checken ! Noch einfügen!
        currentBlock->rotateRight();
}

void GameController::sKeyPressed()
{
    if (checkCanMove(currentBlock, 'd'))
        currentBlock->tryMoveDown();
}

GameController::GameController()
{
    field = create2DArray<Tile *>(rowCount, columnCount); // [Reihe][Spalte]
    moveDownLimiter = 0;
    for(int i = 0; i < 7; i++)
    {
        blocksSpawned[i] = 0;
    }
}

bool GameController::isGameRunning()
{
    return gameRunning;
}

void GameController::update()
{
    if (tryInsertCurrentBlockInField())
        ui.draw(field);

    if (checkCanMove(currentBlock, 'd') && (moveDownLimiter == 10))
    {
        moveDownLimiter = 0;
        currentBlock->tryMoveDown();
    }
    else
    {
        checkRows();
        if(moveDownLimiter==10) // update wird öfters aufgerufen (kleineres Sleep), der Block soll aber nicht jedes mal nach unten
        {
            moveDownLimiter = 0;
            createBlock(); // Am Boden
        }
    }
    moveDownLimiter++;
}

bool GameController::checkCanMove(TetrisBlock *block, char direction)
{
    auto tileCopy = new TetrisBlock(*block);
    auto fieldCopy = field;
    bool noBorder;
    switch (direction)
    {
    case 'l': // left
        noBorder = tileCopy->tryMoveLeft();
        break;
    case 'r': // right
        noBorder = tileCopy->tryMoveRight();
        break;
    case 'd': // down
        noBorder = tileCopy->tryMoveDown();
        break;
    default:
        break;
    }
    if (!noBorder) // Block am Rand -> kein Verschieben möglich
    {
        return false;
    }

    auto tetrisBlockMatrix = tileCopy->buildMatrix();
    auto tetirsBlockMatrixOld = currentBlockLastUpdate->buildMatrix();

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            if (tetirsBlockMatrixOld[i][j] != nullptr)
            {
                if (i != 0 && i != rowCount - 1 && j != 0 && j != columnCount - 1) // Rand außen vor lassen
                    fieldCopy[i][j] = nullptr;                                     // Alte Position vom TetrisBock löschen
            }

            auto tetrisBlockTile = tetrisBlockMatrix[i][j];
            auto matrixBlockTile = fieldCopy[i][j];
            if (tetrisBlockTile != nullptr && matrixBlockTile != nullptr) // Verboten (Position ist nicht frei)
            {
                return false;
            }
        }
    }

    delete tileCopy;
    return true;
}

void GameController::start()
{
    gameRunning = true;
    ui.init(field);
    createBlock();
}

void GameController::finish()
{
}

GameController::~GameController()
{
}