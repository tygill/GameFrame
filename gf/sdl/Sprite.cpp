#include "gf/sdl/Sprite.h"

namespace gf {

    namespace sdl {

        GF_REGISTER_RESOURCE(Sprite);

        Sprite::Sprite(SDL_Surface* surf) :
            sdlSurface(surf)
        {
            sdlSurface->refcount++;
        }

        Sprite::Sprite(const Sprite& other) :
            sdlSurface(other.sdlSurface)
        {
            sdlSurface->refcount++;
        }
        
        Sprite::~Sprite() {
            SDL_FreeSurface(sdlSurface);
        }

        SDL_Surface* Sprite::surface() const {
            return sdlSurface;
        }

    }

}
