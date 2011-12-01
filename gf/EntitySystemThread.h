#pragma once
#ifndef idF0A6916A_634B_4B70_9E8A24A1233AC718
#define idF0A6916A_634B_4B70_9E8A24A1233AC718

#include "gf/Global.h"
// Causes problems in including.
//#include "gf/GameFrame.h"
//#include "gf/EntitySystem.h"

#include <boost/shared_ptr.hpp>

namespace gf {
    
    class EntitySystem;
    
    class EntitySystemThread {
    public:
        EntitySystemThread(GameFrame* frame);
        ~EntitySystemThread();
        
        template<class T> T* addSystem();
        
        // This should be able to handle interrupts, because that's how
        // the game will be closed (so wrap the whole function in a try
        // catch block)
        void operator()();
        
    private:
        EntitySystems systems;
        GameFrame* framework;

    };
    
    // Template implementations
    // ------------------------
    
    template<class T> T* EntitySystemThread::addSystem() {
        boost::shared_ptr<T> system(new T(framework));
        systems.insert(system);
        return system.get();
    }
    
}

#endif // header
