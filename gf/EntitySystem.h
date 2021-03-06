#pragma once
#ifndef idAD4971CA_2B3F_4DC1_A782582BA3F41098
#define idAD4971CA_2B3F_4DC1_A782582BA3F41098

#include "gf/Global.h"

namespace gf {
    
    class EntitySystem {
    public:
        // Subclasses register component sets and messages in the ctor
        EntitySystem(GameFrame* frame) : framework(frame) {}
        virtual ~EntitySystem() {}
        
        // Doesn't do anything by default. This way systems can be
        // created that only do things when entities are added or
        // removed.
        
        // This is where all the new behavior should be .
        virtual void update(boost::chrono::milliseconds delta) {}
        
        // Callbacks - must be reentrant and threadsafe
        // Called by the EntityManager after the system has been registered
        virtual void added(ConstEntityPtr entity) {}
        virtual void removed(ConstEntityPtr entity) {}
        
        virtual void receive(MessagePtr message) {}
        
    protected:
        GameFrame* framework;
    };
    
}

#endif // header
