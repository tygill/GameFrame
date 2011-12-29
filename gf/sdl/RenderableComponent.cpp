#include "gf/sdl/RenderableComponent.h"

namespace gf {

    namespace sdl {
        
        GF_REGISTER_COMPONENT(RenderableComponent);

        RenderableComponent::RenderableComponent() :
            spr(0)
        {
        }

        RenderableComponent::~RenderableComponent() {
        }

        ResourceId RenderableComponent::sprite() const {
            return spr;
        }

        void RenderableComponent::setSprite(ResourceId newSprite) {
            spr = newSprite;
        }

    }

}
