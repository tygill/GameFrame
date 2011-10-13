#pragma once
#ifndef id9E8E45AA_EE0C_441B_9B133AF1195FCE23
#define id9E8E45AA_EE0C_441B_9B133AF1195FCE23

#include "gf/Global.h"

namespace gf {
    
    class EntityTemplate {
    public:
        EntityTemplate();
        ~EntityTemplate();
        
    private:
        friend class EntityManager;
        
        // This is what actually instanciates an entity in the framework.
        // Subclasses can decide if there is some form of state to a template,
        // or if state is static, or if the returned entity always has the same
        // info.
        virtual EntityId create(EntityManager* manager) = 0;
    };
    
}

#endif // header
