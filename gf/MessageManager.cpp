#include "gf/MessageManager.h"
#include "gf/EntitySystem.h"

namespace gf {
    
    MessageManager::MessageManager() {
    }
    
    MessageManager::~MessageManager() {
    }
    
    void MessageManager::send(MessagePtr message) {
        MessageMap::iterator pos = messageMap.find(message->type());
        if (pos != messageMap.end()) {
            std::cout << "Sending message" << std::endl;
            for (boost::unordered_set<EntitySystem*>::iterator itr = pos->second.begin(); itr != pos->second.end(); itr++) {
                (*itr)->receive(message);
            }
        }
    }
    
    // Note: possibly inefficient on the first case of inserting a
    // new type...
    void MessageManager::registerSystem(EntitySystem* system, MessageType type) {
        MessageMap::iterator pos = messageMap.find(type);
        if (pos != messageMap.end()) {
            // We just add it to the set
            pos->second.insert(system);
        } else {
            std::cout << "Creating new message map set" << std::endl;
            // Create a new EntitySystem*s to put the system in
            std::pair<MessageMap::iterator, bool> messagePair = messageMap.insert(std::make_pair(type, boost::unordered_set<EntitySystem*>()));
            messagePair.first->second.insert(system);
        }
    }
    
}
