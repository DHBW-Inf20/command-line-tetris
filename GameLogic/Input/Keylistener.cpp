#include "Keylistener.hpp"
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
//private


int key_press()
{
    KEY_EVENT_RECORD keyevent;
    INPUT_RECORD irec;
    DWORD events;
    while (true)
    {
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &irec, 1, &events);
        if (irec.EventType == KEY_EVENT && ((KEY_EVENT_RECORD &)irec.Event).bKeyDown)
        {
            keyevent = (KEY_EVENT_RECORD &)irec.Event;
            const int ca = (int)keyevent.uChar.AsciiChar;
            const int cv = (int)keyevent.wVirtualKeyCode;
            const int key = ca == 0 ? -cv : ca + (ca > 0 ? 0 : 256);
            switch (key)
            {
            case -16:
                continue; // disable Shift
            case -17:
                continue; // disable Ctrl / AltGr
            case -18:
                continue; // disable Alt / AltGr
            case -220:
                continue; // disable first detection of "^" key (not "^" symbol)
            case -221:
                continue; // disable first detection of "`" key (not "`" symbol)
            case -191:
                continue; // disable AltGr + "#"
            case -52:
                continue; // disable AltGr + "4"
            case -53:
                continue; // disable AltGr + "5"
            case -54:
                continue; // disable AltGr + "6"
            case -12:
                continue; // disable num block 5 with num lock deactivated
            case 13:
                return 10; // enter
            case -46:
                return 127; // delete
            case -49:
                return 251; // ¹
            case 0:
                continue;
            case 1:
                continue; // disable Ctrl + a (selects all text)
            case 2:
                continue; // disable Ctrl + b
            case 3:
                continue; // disable Ctrl + c (terminates program)
            case 4:
                continue; // disable Ctrl + d
            case 5:
                continue; // disable Ctrl + e
            case 6:
                continue; // disable Ctrl + f (opens search)
            case 7:
                continue; // disable Ctrl + g
            //case    8: continue; // disable Ctrl + h (ascii for backspace)
            //case    9: continue; // disable Ctrl + i (ascii for tab)
            case 10:
                continue; // disable Ctrl + j
            case 11:
                continue; // disable Ctrl + k
            case 12:
                continue; // disable Ctrl + l
            //case   13: continue; // disable Ctrl + m (breaks console, ascii for new line)
            case 14:
                continue; // disable Ctrl + n
            case 15:
                continue; // disable Ctrl + o
            case 16:
                continue; // disable Ctrl + p
            case 17:
                continue; // disable Ctrl + q
            case 18:
                continue; // disable Ctrl + r
            case 19:
                continue; // disable Ctrl + s
            case 20:
                continue; // disable Ctrl + t
            case 21:
                continue; // disable Ctrl + u
            case 22:
                continue; // disable Ctrl + v (inserts clipboard)
            case 23:
                continue; // disable Ctrl + w
            case 24:
                continue; // disable Ctrl + x
            case 25:
                continue; // disable Ctrl + y
            case 26:
                continue; // disable Ctrl + z
            default:
                return key; // any other ASCII/virtual character
            }
        }
    }
}
bool Keylistener::isRunning()
{   
    runningMutex.lock();
    auto running = this->running;
    runningMutex.unlock();
    return running;
}
void Keylistener::pollingLoop()
{    
    while (isRunning())
    {  
      
        const int key = key_press(); // blocks until a key is pressed     
        eventHandlerMutex.lock();
        auto match = eventHandlers.find(key);
        eventHandlerMutex.unlock();
        if(match!=eventHandlers.end())
        {
            (match->second)();
        }     
    }
}


//public

Keylistener::Keylistener()
{
}
void Keylistener::startMultithreaded()
{ 
    if(this->isRunning()) return;  
    runningMutex.lock();
    this->running = true;
    runningMutex.unlock();
    std::thread s ([this](){pollingLoop();});    
    s.detach();
}
void Keylistener::stop()
{
    runningMutex.lock();
    this->running = false;
    runningMutex.unlock();
}
void Keylistener::registerHandler(char key, std::function<void()> handler)
{
    eventHandlerMutex.lock();    
    eventHandlers[key] = handler;
    eventHandlerMutex.unlock();
}
void Keylistener::removeHandler(char key)
{
    eventHandlerMutex.lock();    
    eventHandlers.erase(key);
    eventHandlerMutex.unlock();
}
Keylistener::~Keylistener()
{
}