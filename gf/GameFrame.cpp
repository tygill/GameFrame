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
    	for (EntitySystems::iterator itr = entitySystems.begin(); itr != entitySystems.end(); itr++) {
    		threads.insert(new boost::thread(itr.second));
    	}
    }

    EntityManager& GameFrame::entityManager() {
    	return entites;
    }

    ResourceManager& GameFrame::resourceManager() {
    	return resources;
    }

    MessageManager& GameFrame::messageManager() {
    	return messages;
    }

}
