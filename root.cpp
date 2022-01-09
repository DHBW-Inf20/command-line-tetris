
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include "GameLogic/GameController.h"
#include "GameLogic/Input/Keylistener.h"
#include "Utilities/AnsiEscape.h"
#include "GameLogic/Highscores/Highscore.h"
#include "Utilities/MemoryLeakDetection.h"

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

void AnimateString(std::string str, bool linebreak, int delay)
{
    for (int i = 0; i < str.length(); i++) {
        std::cout << str[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    if (linebreak) {
        std::cout << std::endl;
    }
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
    AnimateString(std::string("Game Over"), true, 200);
    AnimateString(std::string(chName), true, 50);
    AnimateString(std::string(chLevel), true, 50);
    AnimateString(std::string(chScore), true, 50);
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
            AnimateString(std::string("Insert your Name: "), true, 100);
            std::string name;
            std::cin >> name;
            auto* controller = new GameController();
            auto* listener = new Keylistener();        	

            listener->Stop();

            listener->RegisterHandler(100, [controller]() {controller->RightKeyPressed();}); // d        
            listener->RegisterHandler(-39, [controller]() {controller->RightKeyPressed();}); // right
            listener->RegisterHandler(97, [controller]() {controller->LeftKeyPressed();}); // a
            listener->RegisterHandler(-37, [controller]() {controller->LeftKeyPressed();}); // left
            listener->RegisterHandler(119, [controller]() {controller->UpKeyPressed();}); // w
            listener->RegisterHandler(-38, [controller]() {controller->UpKeyPressed();}); // up
            listener->RegisterHandler(98, [controller]() {controller->BKeyPressed();}); // b
            listener->RegisterHandler(115, [controller]() {controller->DownKeyPressed();}); // s
      		listener->RegisterHandler(-40, [controller]() {controller->DownKeyPressed();}); // down
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
                });

            game.join();

            listener->Stop();
            controller->Stop();
            const auto score = controller->GetScore();
            const auto level = controller->GetLevel();
            AddHighscore(score, name);
            ShowGameOver(score, name, level);

            showCursor();
            delete controller;
            delete listener;

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

	#ifdef debug
    _CrtDumpMemoryLeaks();
	#endif
}
