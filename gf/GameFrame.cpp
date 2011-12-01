#include "gf/GameFrame.h"
#include "gf/EntitySystemThread.h"

namespace gf {
    
    GameFrame::GameFrame() :
        running(false)
    {
        // Nothing
    }
    
    GameFrame::~GameFrame() {
        // Nothing
    }
    
    int GameFrame::run() {
        running = true;
        if (systemThreads.size() > 1) {
            // Grab the second and rest of the threads. The first thread will be run in the main thread for the sake of SDL and other thread dependant things.
            EntitySystemThreads::iterator itr = systemThreads.begin();
            itr++;
    	    for (; itr != systemThreads.end(); itr++) {
                std::cout << "Creating thread" << std::endl;
    		    threads.create_thread(boost::ref(*itr->second.get()));
                std::cout << "Thread created" << std::endl;
    	    }
        }
        if (systemThreads.size() > 0) {
            systemThreads.begin()->second.get()->operator()();
        }
        threads.join_all();
        return 0;
    }

    bool GameFrame::isRunning() const {
        return running;
    }

    void GameFrame::stop() {
        running = false;
    }

    EntityManager& GameFrame::entityManager() {
    	return entities;
    }

    ResourceManager& GameFrame::resourceManager() {
    	return resources;
    }

    MessageManager& GameFrame::messageManager() {
    	return messages;
    }

}
