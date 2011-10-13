#pragma once
#ifndef idF0A6916A_634B_4B70_9E8A24A1233AC718
#define idF0A6916A_634B_4B70_9E8A24A1233AC718

#include "gf/Global.h"
//#include "gf/EntitySystem.h"

namespace gf {
    
    class EntitySystem;
    
    class EntitySystemThread {
    public:
        EntitySystemThread();
        ~EntitySystemThread();
        
        void addSystem(EntitySystem* system);
        
        // This should be able to handle interrupts, because that's how
        // the game will be closed (so wrap the whole function in a try
        // catch block)
        void operator()();
        
    private:
        EntitySystems systems;
    };
    
}

#endif // header
