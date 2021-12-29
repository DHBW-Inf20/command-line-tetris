
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

#ifndef _cleverlandZ_
#define _cleverlandZ_
#include "../UI/DataClasses/Blocks/CleverlandZ.cpp"
#endif

#include "../UI/UI.cpp"

class GameController
{
private:
    std::atomic<bool> gameRunning = false;
    TetrisBlock* currentBlock;
    TetrisBlock* currentBlockLastUpdate; //Hier wird der Block vom letzten Update gespeichert -> So kann bei einer Änderung das Spielfeld rekonstruiert werden
    std::vector<std::vector<Tile*>> field;
    UI ui;
    bool tryInsertCurrentBlockInField();
    void createBlock();

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
    bool error = false;
    auto tetirsBlockMatrixOld = currentBlockLastUpdate->buildMatrix();
    auto tetrisBlockMatrix = currentBlock->buildMatrix();
    for(int i=0; i<rowCount;i++)
    {
        for(int j=0; j<columnCount;j++)
        {
            if(tetirsBlockMatrixOld[i][j]!=nullptr)
            {                    
                if(i != 0 && i != rowCount-1 && j != 0 && j != columnCount-1) // Rand außen vor lassen
                    field[i][j] = nullptr; //Alte Position vom TetrisBock löschen
            }                
            auto tetrisBlockTile = tetrisBlockMatrix[i][j];
            auto matrixBlockTile = field[i][j];
            if(tetrisBlockTile!=nullptr && matrixBlockTile!=nullptr)   //Verboten (Position ist nicht frei)
            {               
                error =  true; 
                //TODO: Rollback
            }      
            else if(tetrisBlockTile!=nullptr && matrixBlockTile==nullptr)  //Feld wird gesetzt
            {
                field[i][j] = tetrisBlockTile;
            }
        }   
    }
  
    currentBlockLastUpdate =  new TetrisBlock(*currentBlock);  //TODO: Alte Löschen?
    return !error;
}

void GameController::createBlock()
{
    currentBlock = new CleverlandZ();
    currentBlockLastUpdate = currentBlock;
}
void GameController::bKeyPressed()
{       
    gameRunning = false;
    printf("b pressed\n");
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
    field = create2DArray<Tile*> (rowCount, columnCount); // [Reihe][Spalte]
}

bool GameController::isGameRunning()
{
    return gameRunning;
}

void GameController::update()
{
    if(tryInsertCurrentBlockInField())
        ui.draw(field);
    if(!currentBlock->tryMoveDown())
        createBlock(); //Am Boden
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