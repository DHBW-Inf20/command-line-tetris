#include "Keylistener.h"
#include "keylib.h"
#include <thread>
#include "../../Utilities/MemoryLeakDetection.h"

/* Gibt Auskunft ob der Keylistener aktiv ist */
bool Keylistener::IsRunning() const
{
    RunningMutex.lock();
    const auto running = this->running;
    RunningMutex.unlock();
    return running;
}

/* Prüft auf Tastendruck und ruft ggf. passende Funktion auf */
void Keylistener::PollingLoop()
{    
    while (IsRunning())
    {      
        const auto key = key_press(); // blocks until a key is pressed      
        EventHandlerMutex.lock();
        auto match = EventHandlers.find(key);
        EventHandlerMutex.unlock();
        if(match!=EventHandlers.end())
        {
            (match->second)();
        }     
    }
}

Keylistener::Keylistener(): running(false)
{
}

void Keylistener::StartMultithreaded()
{ 
    if(this->IsRunning()) return;  
    RunningMutex.lock();
    this->running = true;
    RunningMutex.unlock();
    std::thread s ([this](){PollingLoop();});    
    s.detach();
}

void Keylistener::Stop()
{
    RunningMutex.lock();
    this->running = false;
    RunningMutex.unlock();
}

/* Registiert eine Taste, welche nun überwacht wird */
void Keylistener::RegisterHandler(const int key, const std::function<void()> handler)
{
    EventHandlerMutex.lock();    
    EventHandlers[key] = handler;
    EventHandlerMutex.unlock();
}

void Keylistener::RemoveHandler(const int key)
{
    EventHandlerMutex.lock();    
    EventHandlers.erase(key);
    EventHandlerMutex.unlock();
}

Keylistener::~Keylistener()
{
}