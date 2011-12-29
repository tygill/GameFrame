#pragma once
#ifndef id591B51E7_32B2_4D94_874C867F218E4213
#define id591B51E7_32B2_4D94_874C867F218E4213

#include "gf/sdl/GameFrameSDL.h"
#include "gf/EntitySystem.h"

namespace gf {
    
    namespace sdl {
        
        class SDLEventSystem : public EntitySystem {
        public:
            SDLEventSystem(GameFrame* frame);
            ~SDLEventSystem();

            void update(boost::chrono::milliseconds delta);

        };
        
    }
    
}

#endif // header
