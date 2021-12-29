
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

#include "../UI/UI.cpp"

class GameController
{
private:
    std::atomic<bool> gameRunning = false;
    TetrisBlock* currentBlock;
    std::vector<std::vector<Tile*>> field;
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
    field = create2DArray<Tile*> (dimensionRow, dimensionColumn); // [Reihe][Spalte]
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