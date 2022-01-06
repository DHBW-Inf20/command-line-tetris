#include "Keylistener.hpp"
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "keylib.h"


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

void Keylistener::registerHandler(int key, std::function<void()> handler)
{
    eventHandlerMutex.lock();    
    eventHandlers[key] = handler;
    eventHandlerMutex.unlock();
}

void Keylistener::removeHandler(int key)
{
    eventHandlerMutex.lock();    
    eventHandlers.erase(key);
    eventHandlerMutex.unlock();
}

Keylistener::~Keylistener()
{
}