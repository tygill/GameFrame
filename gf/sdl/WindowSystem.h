#pragma once
#ifndef id9B08F9A9_A856_4307_9ECD4FA49467F5ED
#define id9B08F9A9_A856_4307_9ECD4FA49467F5ED

#include "gf/EntitySystem.h"

#include <SDL.h>

namespace gf {

    namespace sdl {
        
        class WindowSystem : public gf::EntitySystem {
        public:
            WindowSystem(GameFrame* frame);
            ~WindowSystem();
            
            void update(boost::chrono::milliseconds delta);
            
        private:
            SDL_Surface* screen;
            ComponentTypes types;

        };
        
    }

}

#endif // header
