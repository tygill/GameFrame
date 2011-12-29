#pragma once
#ifndef id621D4E9B_65DC_4B1F_B8F7037BB03D3BB9
#define id621D4E9B_65DC_4B1F_B8F7037BB03D3BB9

#include "gf/Resource.h"
#include "gf/sdl/Sprite.h"

#include <SDL.h>

namespace gf {

    namespace sdl {
        
        class Sprite : public gf::Resource {
        public:
            Sprite(SDL_Surface* surf);
            Sprite(const Sprite& other);
            ~Sprite();

            GF_DECLARE_RESOURCE;

            SDL_Surface* surface() const;

        private:
            // Each copy of the Sprite should increment the refcount of the surface, and should call free on it.
            SDL_Surface* sdlSurface;

        };

        typedef boost::shared_ptr<Sprite> SpritePtr;
        typedef boost::shared_ptr<Sprite const> ConstSpritePtr;
    
    }

}

#endif // header
