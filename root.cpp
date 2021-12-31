
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "GameLogic/GameController.cpp"
#include "GameLogic/Input/Keylistener.hpp"
#include "Highscores/Highscore.cpp"

int showStartMenuSelect(){
    clearScreen();
    std::string selection;
    std::cout   <<"Welcome to our Tetris project" << std::endl
                <<"Select what you want to do" << std::endl
                <<"1:\t Start a new game" << std::endl
                <<"2:\t View the highscores" << std::endl
                <<"0:\t Close the application" << std::endl;
    std::cin >> selection;
 
    return std::atoi(selection.c_str());
}

int main()
{    
    while(true)
    {
        int selection = showStartMenuSelect();
        switch (selection)
        {
        case 1:{
            GameController* controller  = new GameController();
            Keylistener* listener = new Keylistener();

            listener->stop();

            listener->registerHandler('d', [controller]() {controller->dKeyPressed();});
            listener->registerHandler('a', [controller]() {controller->aKeyPressed();});
            listener->registerHandler('w', [controller]() {controller->wKeyPressed();});
            listener->registerHandler('b', [controller]() {controller->bKeyPressed();});
            listener->registerHandler('s', [controller]() {controller->sKeyPressed();});
            listener->startMultithreaded(); 

            std::thread game([controller, listener]()
            {
                controller->start();    
                while (controller->isGameRunning())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    controller->update();        
                }
                delete controller;
                delete listener;
            });
            game.join();
            break;
        }
        case 2:
            showHighscore();
            break;
        default:
            std::cout << "This is not a valid option\n";
            break;
        }
    }
}
