#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP

#include <map>
#include <shared_mutex>
#include <functional>


class Keylistener
{
    public:
        Keylistener();
       ~Keylistener();
	
		void StartMultithreaded();
        void Stop();
        void RegisterHandler(int key, std::function<void()> handler);
        void RemoveHandler(int key);

	private:
        std::map<int, std::function<void()>> EventHandlers;
        bool running;      
        mutable std::shared_mutex EventHandlerMutex;
        mutable std::shared_mutex RunningMutex;

        bool IsRunning() const;
        void PollingLoop();
};

#endif //KEYLISTENENER_H