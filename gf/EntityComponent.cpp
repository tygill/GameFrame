#include "gf/EntityComponent.h"

namespace gf {
    
    ComponentType EntityComponent::type() const {
        return ComponentType(typeid(this));
    }
    
}
