#pragma once
#ifndef idAD4971CA_2B3F_4DC1_A782582BA3F41098
#define idAD4971CA_2B3F_4DC1_A782582BA3F41098

#include "gf/Global.h"

namespace gf {
    
    class EntitySystem {
    public:
        EntitySystem();
        ~EntitySystem();
        
        // This is where all the new behavior should be added
        virtual void update(boost::chrono::milliseconds delta);
        
        // Callbacks - must be reentrant and threadsafe
        // Called by the EntityManager after the system has been registered
        virtual void added(EntityPtr entity);
        virtual void removed(EntityPtr entity);
        
    private:
        GameFrame* framework;
    };
    
}

#endif // header
