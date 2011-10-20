#pragma once
#ifndef id3C94EC5B_165E_4A78_A9812964538C70F0
#define id3C94EC5B_165E_4A78_A9812964538C70F0

#include "gf/Global.h"
#include "gf/Message.h"

namespace gf {
    
    class MessageManager {
    public:
        MessageManager();
        ~MessageManager();
        
        // Sends the defaultly instanciated version of T
        template<class T> void send();
        
        // Thought this would be good, but the message manager would
        // need to cache the message to return a shared_ptr to it, so
        // instead, let the system handle this.
        //boost::shared_ptr<Message> create() const;
        void send(MessagePtr message);
        
        // Setup systems
        void registerSystem(EntitySystem* system, MessageType type);
        
    private:
        typedef boost::unordered_map<MessageType, boost::unordered_set<EntitySystem*> > MessageMap;
        MessageMap messageMap;
        
    };
    
    template<class T> void MessageManager::send() {
        boost::shared_ptr<T> message(new T());
        send(message);
    }
    
}

#endif // header
