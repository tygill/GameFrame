#include "gf/Resource.h"

namespace gf {
    
    ResourceType Resource::nextRegistrationType = 1;
    
    Resource::Resource()
    {
    }

    Resource::~Resource() {
    }

    ResourceType Resource::type() const {
        throw MethodNotDefinedException("Resource::type() was not redefined in a subclass. Did a custom resource class not have a GF_DECLARE_RESOURCE macro?");
    }
    
    ResourceType Resource::registerType() {
        return nextRegistrationType++;
    }
    
}
