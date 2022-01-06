
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include "GameLogic/GameController.h"
#include "GameLogic/Input/Keylistener.h"
#include "Highscores/Highscore.h"
#include "Utilities/AnsiEscape.h"

#ifdef _WIN32
#include <windows.h>
#endif

int ShowStartMenuSelect()
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

    auto res = -1;
    try
    {
        res =  std::stoi(selection.c_str());
    }
    catch(...)
    {
        
    }
    return res;
}

void ShowGameOver(const int score, const std::string name, const int level)
{
	const auto tempScore = "Score: " + std::to_string(score);
	const auto tempLevel = "Level: " + std::to_string(level);
	const auto tempName = "Name: " + name;
	const auto* chName = tempName.c_str();
	const auto* chScore = tempScore.c_str();
	const auto* chLevel = tempLevel.c_str();

    clearScreen();
    moveTo(0,0);
    puts("GAME OVER \n");
    puts(chName);
    puts(chLevel);
    puts(chScore);
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
}

int main()
{
    setupConsole();
    restoreConsole();
    #ifdef _WIN32
    // Make utf8 vaible
    SetConsoleOutputCP(CP_UTF8);
    #endif
    while(const auto selection = ShowStartMenuSelect())
    {
        switch (selection)
        {
        case 1:{
            printf("Insert your Name: ");
            std::string name;
            std::cin >> name;

            auto* controller = new GameController();
            auto* listener = new Keylistener();

            listener->Stop();

            listener->RegisterHandler(100, [controller]() {controller->DKeyPressed();}); // d
            listener->RegisterHandler(97, [controller]() {controller->AKeyPressed();}); // a
            listener->RegisterHandler(119, [controller]() {controller->WKeyPressed();}); // w
            listener->RegisterHandler(98, [controller]() {controller->BKeyPressed();}); // b
            listener->RegisterHandler(115, [controller]() {controller->SKeyPressed();}); // s
            listener->RegisterHandler(32, [controller]() {controller->EnterKeyPressed();}); // enter
            listener->StartMultithreaded(); 

            std::thread game([controller, listener, name]()
            {
                controller->Start();    
                while (controller->IsGameRunning())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    controller->Update();        
                }
                listener->Stop();
                controller->Stop();

                const auto score = controller->GetScore();
                const auto level = controller->GetLevel();
                AddHighscore(score, name);
                ShowGameOver(score, name, level);

                delete controller;
                delete listener;
                showCursor();
            });
            game.join();
            break;
        }
        case 2:     
            clearScreen();
            moveTo(0,0);
            ShowHighscore();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            break;
        default:
            std::cout << "This is not a valid option\n";
            break;
        }
    }
}
