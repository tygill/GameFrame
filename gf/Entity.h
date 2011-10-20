#pragma once
#ifndef id8139993E_0BD5_45E1_BCC7AE12F8B8A95E
#define id8139993E_0BD5_45E1_BCC7AE12F8B8A95E

#include "gf/Global.h"
#include "gf/EntityComponent.h"

namespace gf {
    
    class Entity {
    public:
        // No construction/deletion necessary
        //Entity();
        //~Entity();
        
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
    
    // Template function definitions
    // -----------------------------
    
    template<class T> boost::shared_ptr<T> Entity::addComponent() {
        boost::shared_ptr<T> component(new T());
        ComponentType type(componentType<T>());
        types.insert(type);
        components.insert(std::pair<ComponentType, boost::shared_ptr<EntityComponent> >(type, component));
        return component;
    }
    
    template<class T> bool Entity::hasComponent() const {
        return types.find(componentType<T>()) == types.end();
    }
    
    template<class T> boost::shared_ptr<T> Entity::getComponent() const {
        ComponentMap::const_iterator pos = components.find(componentType<T>());
        if (pos != components.end()) {
            return pos->second;
        } else {
            return boost::shared_ptr<T>();
        }
    }
    
    template<class T> bool Entity::removeComponent() {
        return components.erase(componentType<T>()) > 0;
    }
    
}

#endif // header
