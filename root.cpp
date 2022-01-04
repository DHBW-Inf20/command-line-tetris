
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "GameLogic/GameController.cpp"
#include "GameLogic/Input/Keylistener.hpp"
#include "Highscores/Highscore.cpp"

int showStartMenuSelect(){
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
    while(int selection = showStartMenuSelect())
    {
        switch (selection)
        {
        case 1:{
            GameController* controller  = new GameController();
            Keylistener* listener = new Keylistener();

            listener->stop();

            listener->registerHandler(100, [controller]() {controller->dKeyPressed();}); // d
            listener->registerHandler(97, [controller]() {controller->aKeyPressed();}); // a
            listener->registerHandler(119, [controller]() {controller->wKeyPressed();}); // w
            listener->registerHandler(98, [controller]() {controller->bKeyPressed();}); // b
            listener->registerHandler(115, [controller]() {controller->sKeyPressed();}); // s
            listener->registerHandler(32, [controller]() {controller->enterKeyPressed();}); // enter
            listener->startMultithreaded(); 

            std::thread game([controller, listener]()
            {
                controller->start();    
                while (controller->isGameRunning())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    controller->update();        
                }
                controller->stop();
                listener->stop();
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
