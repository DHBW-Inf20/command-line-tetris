#include "../UI/DataClasses/TetrisBlock.cpp"

#include <chrono>
#include <thread>
#include <atomic>
#include "../Utilities/AnsiEscape.h"

class GameController
{
private:
 
    std::atomic<bool> gameRunning = false;
    TetrisBlock currentBlock;

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