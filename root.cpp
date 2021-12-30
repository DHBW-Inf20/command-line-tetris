
#include <chrono>
#include <thread>
#include <atomic>
#include "GameLogic/GameController.cpp"
#include "GameLogic/Input/Keylistener.hpp"

int main()
{    
    GameController* controller  = new GameController();
    Keylistener* listener = new Keylistener();

    listener->stop();

    listener->registerHandler('d', [controller]() {controller->dKeyPressed();});
    listener->registerHandler('a', [controller]() {controller->aKeyPressed();});
    listener->registerHandler('w',[controller]() {controller->wKeyPressed();});
    listener->registerHandler('b',[controller]()  {controller->bKeyPressed();});
    listener->startMultithreaded(); 

   std::thread game([controller, listener]()
    {
        controller->start();    
        while (controller->isGameRunning())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            controller->update();        
        }
        delete controller;
        delete listener;
    });
    game.join();

}
