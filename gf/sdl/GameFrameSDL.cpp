#include "gf/sdl/GameFrameSDL.h"

#include <SDL.h>

namespace gf {

    namespace sdl {

        void init() {
            // SDL_INIT_TIMER|SDL_INIT_EVENTTHREAD|
            SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
        }

        void quit() {
            SDL_Quit();
        }

    }

}
