#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP
#include <map>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <functional>


class Keylistener{
    private:
        std::map<int, std::function<void()>> eventHandlers;
        bool running;      
        mutable std::shared_mutex eventHandlerMutex;
        mutable std::shared_mutex runningMutex;

        bool isRunning();
        void pollingLoop();
    public:
        Keylistener();
        void startMultithreaded();
        void stop();
        void registerHandler(int key, std::function<void()> handler);
        void removeHandler(int key);
        ~Keylistener();
};

#endif