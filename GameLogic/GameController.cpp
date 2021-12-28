#include "../UI/DataClasses/TetrisBlock.cpp"

#include "../UI/DataClasses/Blocks/BlueRicky.cpp"

#include <chrono>
#include <thread>
#include <atomic>
#include "../UI/UI.cpp"

class GameController
{
private:
    std::atomic<bool> gameRunning = false;
    TetrisBlock* currentBlock;
    UI ui;

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
    ui.draw();
}

void GameController::start()
{
    gameRunning = true;   
}

void GameController::finish()
{

}

GameController::~GameController()
{
    
}