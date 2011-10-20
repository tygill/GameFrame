#include "gf/GameFrame.h"
#include "gf/EntitySystemThread.h"

namespace gf {
    
    GameFrame::GameFrame() {
        // Nothing
    }
    
    GameFrame::~GameFrame() {
        // Nothing
    }
    
    int GameFrame::run() {
    	for (EntitySystemThreads::iterator itr = systemThreads.begin(); itr != systemThreads.end(); itr++) {
    		threads.create_thread(boost::ref(*(itr->second)));
    	}
        threads.join_all();
        return 0;
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
