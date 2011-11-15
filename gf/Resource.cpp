#include "gf/Resource.h"

namespace gf {
    
    ResourceType Resource::type() const {
        return ResourceType(typeid(*this));
    }
    
}
