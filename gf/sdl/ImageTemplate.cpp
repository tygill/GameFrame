#include "gf/sdl/ImageTemplate.h"

#include "gf/sdl/Sprite.h"
#include <SDL_image.h>

namespace gf {

    namespace sdl {
        
        ImageTemplate::ImageTemplate(std::string file) :
            filename(file)
        {
        }

        ResourcePtr ImageTemplate::create() {
            std::cout << "Loading: " << filename << std::endl;
            SDL_Surface* surface = IMG_Load(filename.c_str());
            std::cout << (surface ? "Surface loaded" : "Surface not loaded") << std::endl;
            boost::shared_ptr<Sprite> sprite(new Sprite(surface));
            // There should eventually be some sort of error checking, probably.
            if (!sprite) {
                std::cout << "Failed to load image: " << filename << std::endl;
            } else {
                std::cout << "Image loaded: " << filename << std::endl;
            }
            return sprite;
        }

    }

}

