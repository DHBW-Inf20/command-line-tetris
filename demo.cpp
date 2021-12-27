#include "Keylistener.hpp"

#include <chrono>
#include <thread>
#include <atomic>
#include "AnsiEscape.h"

Keylistener listener;
std::atomic<bool> gameRunning = false;

void aPressed();
void dPressed();
void bPressed();
void update();
void start();

int pos = 0;

int main()
{
    listener.registerHandler('d', dPressed);
    listener.registerHandler('a', aPressed);
    listener.registerHandler('b', bPressed);

    listener.startMultithreaded();
    gameRunning = true;

    std::thread game([]()
    {
        start();
        while (gameRunning)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            update();
        }
    });
    game.join();
}

void aPressed()
{   
    pos --;
}
void dPressed()
{   
    pos ++;
}

void bPressed()
{
    printf("B pressed\n");
    listener.stop();
    gameRunning = false;
    printf("game Stopped\n");
}

void start()
{
    hideCursor();
    printf("--------------------------\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("--------------------------\n");
}


void update()
{
    moveUp(4);
    clearLine();
    moveRight(pos);
    puts(".");   
    moveDown(3);
}
