#include "../UI/DataClasses/TetrisBlock.cpp"

#include "../UI/DataClasses/Blocks/BlueRicky.cpp"

#include <chrono>
#include <thread>
#include <atomic>

#ifndef _config_
#define _config_
#include "../../UI/Config.cpp"
#endif

#include "../UI/UI.cpp"

class GameController
{
private:
    std::atomic<bool> gameRunning = false;
    TetrisBlock* currentBlock;
    Tile * field [dimensionColumn][dimensionRow]; // [Reihe][Spalte]
    UI ui;
    void insertCurrentBlockInField();

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

void GameController::insertCurrentBlockInField()
{
    

}
void GameController::bKeyPressed()
{       
    gameRunning = false;
    printf("b pressed\n");
}

void GameController::dKeyPressed()
{

}

void GameController::aKeyPressed()
{

}

void GameController::wKeyPressed()
{

}

GameController::GameController()
{

}

bool GameController::isGameRunning()
{
    return gameRunning;
}

void GameController::update()
{
    ui.draw(field);
}

void GameController::start()
{
    gameRunning = true;   
    ui.init(field);
}

void GameController::finish()
{

}

GameController::~GameController()
{
    
}