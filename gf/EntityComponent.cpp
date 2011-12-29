#include "gf/EntityComponent.h"

namespace gf {

    ComponentType EntityComponent::nextRegistrationType = 1;
    
    EntityComponent::EntityComponent()
    {
    }
    
    EntityComponent::~EntityComponent() {
    }
    
    ComponentType EntityComponent::type() const {
        throw MethodNotDefinedException("EntityComponent::type() was not redefined in a subclass. Did a custom component class not have a GF_DECLARE_COMPONENT macro?");
    }
    
    ComponentType EntityComponent::registerType() {
        return nextRegistrationType++;
    }
    
}
