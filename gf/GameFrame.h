#pragma once
#ifndef idCE633B91_11A4_4E7F_84ECFC08322327EE
#define idCE633B91_11A4_4E7F_84ECFC08322327EE

#include "gf/Global.h"
#include "gf/EntityManager.h"
#include "gf/ResourceManager.h"
#include "gf/MessageManager.h"
#include "gf/EntitySystem.h"
#include "gf/EntitySystemThread.h"

#include <boost/thread.hpp>

namespace gf {
    
    class GameFrame {
    public:
        GameFrame();
        ~GameFrame();
        
        template<class T> T* addSystem(uint8_t thread = 0);
        
        // This is what actually builds the threads (0 is the main() thread)
        // It adds them all to a thread group, and then runs them until
        // they all stop. This is designed to be the return to main(), so
        // error codes can be returned as ints.
        int run();

        bool isRunning() const;
        void stop();
        
        EntityManager& entityManager();
        ResourceManager& resourceManager();
        MessageManager& messageManager();
        
    private:
        typedef boost::unordered_map<uint8_t, boost::shared_ptr<EntitySystemThread> > EntitySystemThreads;
        EntitySystemThreads systemThreads;
        
        boost::thread_group threads;
        bool running;
        
        EntityManager entities;
        ResourceManager resources;
        MessageManager messages;

    };
    
    template<class T> T* GameFrame::addSystem(uint8_t thread) {
        // We need to find out if this thread exists yet
        EntitySystemThreads::iterator pos = systemThreads.find(thread);
    	if (pos == systemThreads.end()) {
            // A new thread should be created
            systemThreads.insert(std::make_pair(thread, new EntitySystemThread(this)));
            pos = systemThreads.find(thread);
    		return pos->second->addSystem<T>();
    	} else {
    		return pos->second->addSystem<T>();
    	}
    }

}

#endif // header
