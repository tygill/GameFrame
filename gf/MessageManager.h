#pragma once
#ifndef id3C94EC5B_165E_4A78_A9812964538C70F0
#define id3C94EC5B_165E_4A78_A9812964538C70F0

#include "gf/Global.h"

namespace gf {
    
    class MessageManager {
    public:
        MessageManager();
        ~MessageManager();
        
        // Sends the defaultly instanciated version of T
        template<class T> void send();
        
        boost::shared_ptr<Message> create() const;
        void send(boost::shared_ptr<Message> message);
        
        // Setup systems
        void registerSystem(EntitySystem* system, MessageType type);
        
    private:
        typedef boost::unordered_map<MessageType, boost::unordered_set<EntitySystem*> > MessageMap;
        MessageMap messageMap;
        
    };
    
}

#endif // header
