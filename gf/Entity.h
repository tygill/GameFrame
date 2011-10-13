#pragma once
#ifndef id8139993E_0BD5_45E1_BCC7AE12F8B8A95E
#define id8139993E_0BD5_45E1_BCC7AE12F8B8A95E

#include "gf/Global.h"

namespace gf {
    
    class Entity {
    public:
        Entity();
        ~Entity();
        
        /* T extends EntityComponent */
        template<class T> boost::shared_ptr<T> addComponent();
        template<class T> bool hasComponent() const;
        template<class T> boost::shared_ptr<T> getComponent() const;
        template<class T> bool removeComponent();
        
        ComponentTypes getTypes() const;
        
    private:
        typedef boost::unordered_map<ComponentType, boost::shared_ptr<EntityComponent> > ComponentMap;
        
    private:
        ComponentTypes types;
        ComponentMap components;
    };
    
}

#endif // header
