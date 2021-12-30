
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
    bool tryInsertCurrentBlockInField();
    void createBlock();
    bool checkCanMoveDown(TetrisBlock *block);
    void checkRows();
    void deleteRow(int row);

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

void GameController::createBlock()
{

    switch (GetRandomNumberBetween(0, 6)) 
    {
    case 0:
        currentBlock = new BlueRicky();
        break;
    case 1:
        currentBlock = new CleverlandZ();
        break;
    case 2:
        currentBlock = new Hero();
        break;
    case 3:
        currentBlock = new OrangeRicky();
        break;
    case 4:
        currentBlock = new RhodeIslandZ();
        break;
    case 5:
        currentBlock = new Smashboy();
        break;
    case 6:
        currentBlock = new Teewee();
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
    currentBlock->moveRight();
}

void GameController::aKeyPressed()
{
    currentBlock->moveLeft();
}

void GameController::wKeyPressed()
{
    currentBlock->rotateRight();
}

GameController::GameController()
{
    field = create2DArray<Tile *>(rowCount, columnCount); // [Reihe][Spalte]
}

bool GameController::isGameRunning()
{
    return gameRunning;
}

void GameController::update()
{

    if (tryInsertCurrentBlockInField())
        ui.draw(field);

   
    if (checkCanMoveDown(currentBlock))
    {
        currentBlock->tryMoveDown();
    }
    else
    {
        checkRows();
        createBlock(); // Am Boden
    }

}

bool GameController::checkCanMoveDown(TetrisBlock *block)
{
    auto tileCopy = new TetrisBlock(*block);
    auto fieldCopy = field;
    if (!tileCopy->tryMoveDown())
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