
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "GameLogic/GameController.cpp"
#include "GameLogic/Input/Keylistener.hpp"
#include "Highscores/Highscore.cpp"

int showStartMenuSelect()
{
    moveTo(0,0);
    clearScreen();
    std::string selection;
    std::cout   <<"Welcome to our Tetris project" << std::endl
                <<"Select what you want to do" << std::endl
                <<"1:\t Start a new game" << std::endl
                <<"2:\t View the highscores" << std::endl
                <<"0:\t Close the application" << std::endl;
    std::cin >> selection;
    
    int res = -1;
    try
    {
        res =  std::stoi(selection.c_str());
    }
    catch(...)
    {
        
    }
    return res;
}

int main()
{    
    while(int selection = showStartMenuSelect())
    {
        switch (selection)
        {
        case 1:{
            printf("Insert your Name: ");
            std::string name;
            std::cin >> name;
            
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

            std::thread game([controller, listener, name]()
            {
                controller->start();    
                while (controller->isGameRunning())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    controller->update();        
                }
                listener->stop();
                controller->stop();

                int score = controller->getScore();
                addHighscore(score, name);
                
                delete controller;
                delete listener;
            });
            game.join();
            break;
        }
        case 2:
            clearScreen();
            moveTo(0,0);
            showHighscore();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            break;
        default:
            std::cout << "This is not a valid option\n";
            break;
        }
    }
}
