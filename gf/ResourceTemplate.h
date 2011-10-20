#pragma once
#ifndef id6C46516B_444B_4C13_A68C3CAA516AC207
#define id6C46516B_444B_4C13_A68C3CAA516AC207

#include "gf/Global.h"

namespace gf {
    
    class ResourceManager;
    
    class ResourceTemplate {
    public:
        ResourceTemplate() {}
        virtual ~ResourceTemplate() {}
        
    private:
        friend class ResourceManager;
        
        // This is what actually instanciates an entity in the framework.
        // Subclasses can decide if there is some form of state to a template,
        // or if state is static, or if the returned entity always has the same
        // info.
        virtual boost::shared_ptr<Resource> create(ResourceManager* framework) = 0;
    };
    
}

#endif // header
