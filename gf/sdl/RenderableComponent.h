#pragma once
#ifndef id0144AF27_B478_4713_AD11DE4CE25D815A
#define id0144AF27_B478_4713_AD11DE4CE25D815A

#include "gf/EntityComponent.h"

namespace gf {

    namespace sdl {
    
        class RenderableComponent : public gf::EntityComponent {
        public:
            RenderableComponent();
            ~RenderableComponent();

            GF_DECLARE_COMPONENT;

            ResourceId sprite() const;
            void setSprite(ResourceId newSprite);

        private:
            // Maps each Sprite to a specific depth
            //std::multimap<int, SpritePtr> sprites;

            // Should map to a resource of type Sprite
            ResourceId spr;

        };
    
    }

}

#endif // header
