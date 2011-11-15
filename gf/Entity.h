#pragma once
#ifndef id8139993E_0BD5_45E1_BCC7AE12F8B8A95E
#define id8139993E_0BD5_45E1_BCC7AE12F8B8A95E

#include "gf/Global.h"
#include "gf/EntityComponent.h"

namespace gf {
    
    class Entity {
    public:
        Entity();
        Entity(const Entity& other);
        ~Entity();
        
        bool operator==(const Entity& other) const;
        
        /* T extends EntityComponent */
        template<class T> boost::shared_ptr<T> addComponent();
        template<class T> bool hasComponent() const;
        template<class T> boost::shared_ptr<T> getComponent() const;
        template<class T> bool removeComponent();
        
        ComponentTypes types() const;
        
        void setId(EntityId newId);
        EntityId id() const;
        
    private:
        typedef boost::unordered_map<ComponentType, ComponentPtr> ComponentMap;
        
    private:
        ComponentTypes componentTypes;
        ComponentMap components;
        
        EntityId entId;
        static EntityId nextId;
    };
    
    // Allow storage of Entity objects in unordered_set
    std::size_t hash_value(const Entity& ent);
    
    // Template function definitions
    // -----------------------------
    
    template<class T> boost::shared_ptr<T> Entity::addComponent() {
        // Make sure the entitiy doesn't have a component of this type already
        boost::shared_ptr<T> ent = getComponent<T>();
        if (!ent) {
            boost::shared_ptr<T> component(new T());
            ComponentType type(componentType<T>());
            componentTypes.insert(type);
            components.insert(std::make_pair(type, component));
            return component;
        } else {
            return ent;
        }
    }
    
    template<class T> bool Entity::hasComponent() const {
        return componentTypes.find(componentType<T>()) != componentTypes.end();
    }
    
    template<class T> boost::shared_ptr<T> Entity::getComponent() const {
        ComponentMap::const_iterator pos = components.find(componentType<T>());
        if (pos != components.end()) {
            return boost::static_pointer_cast<T>(pos->second);
        } else {
            return boost::shared_ptr<T>();
        }
    }
    
    template<class T> bool Entity::removeComponent() {
        return components.erase(componentType<T>()) > 0 && componentTypes.erase(componentType<T>()) > 0;
    }
    
}

#endif // header
