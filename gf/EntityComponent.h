#pragma once
#ifndef id7533F2D8_5E80_4B45_902AF88DD7836049
#define id7533F2D8_5E80_4B45_902AF88DD7836049

#include "gf/Global.h"

namespace gf {
    
    class EntityComponent {
    public:
        EntityComponent() {}
        virtual ~EntityComponent() {}
        
        // ComponentType is simply the typeid() of the subclass, but this should
        // hide away that abstraction, and allow access no matter what type of
        // reference you have to the component.
        
        // When you have an actual component
        ComponentType type() const;
        // When you have an unknown component
        //static ComponentType type(EntityComponent* component);
        // When you know the name of the components type
        //template<class T> static ComponentType getType();
        // Supersceded by the global componentType<T>() function
    };
    
}

#endif // header
