#pragma once
#ifndef idAE2BE7B6_9D35_4832_93CD220B7F0597C8
#define idAE2BE7B6_9D35_4832_93CD220B7F0597C8

#include "gf/Global.h"

namespace gf {
    
    typedef std::set<ComponentType> OrderedComponentTypes;
    
    class EntityManager {
    public:
        EntityManager();
        ~EntityManager();
        
        EntityId create();
        EntityId create(EntityTemplate* form);
        bool exists(entityId entId) const;
        bool destroy(EntityId entId);
        
        template<class T> boost::shared_ptr<T> addComponent(EntityId entId);
        template<class T> bool hasComponent(EntityId entId) const;
        template<class T> boost::shared_ptr<T> getComponent(EntityId entId) const;
        template<class T> bool removeComponent(EntityId entId);
        
        // Entity access
        ConstEntityPtr getEntity(EntityId entId) const;
        
        /* T extends EntityComponent */
        template<class T> ConstEntityPtrs getEntities() const;
        ConstEntityPtrs getEntities(ComponentType type) const;
        ConstEntityPtrs getEntities(const ComponentTypes& types) const;
        
        void registerSystem(EntitySystem* system, ComponentType type);
        void registerSystem(EntitySystem* system, const ComponentTypes& types);
        
    private:
        // Mutable Entity access is internal only
        EntityPtr getEntity(EntityId entId);
        
    private:
        // Set up the EntityComponentTree and Entity classes as other files.
        // Then figure out what this needs to have as member variables.
        class EntityComponentTree;
        boost::scoped_ptr<EntityComponentTree> components;
        
        Entities entities;
        EntityId nextId;
    };
    
    
    // EntityManager Helper Classes
    // ----------------------------
    
    class EntityManager::EntityComponentTree {
    public:
        EntityComponentTree();
        ~EntityComponentTree();
        
        // Entity retreval
        ConstEntityPtrs getEntities(ComponentType type) const;
        ConstEntityPtrs getEntities(const OrderedComponentTypes& types) const;
        
        // Todo: Fix component caching (cache on two factors - add and remove)
        // Component caching management
        void addComponent(ConstEntityPtr entity, ComponentType type);
        void removeComponent(ConstEntityPtr entity, ComponentType type);
        //void cacheComponents(ConstEntityPtr entity);
        void removeEntity(ConstEntityPtr entity);
        
        void registerSystem(EntitySystem* system, ComponentType type);
        void registerSystem(EntitySystem* system, const OrderedComponentTypes& types);
        
    private:
        class EntityComponentTreeNode;
        typedef boost::weak_ptr<EntityComponentTreeNode> Node;
        
        void addComponent(ConstEntityPtr entity, ComponentType type, OrderedComponentTypes& types, Node node);
        void removeComponent(ConstEntityPtr entity, ComponentType type, OrderedComponentTypes& types, Node node);
        //void cacheComponents(ConstEntityPtr, OrderedComponentTypes& types, Node node);
        void removeEntity(ConstEntityPtr entity, Node node);
        
    private:
        boost::shared_ptr<EntityComponentTreeNode> root;
    };
    
    class EntityManager::EntityComponentTree::EntityComponentTreeNode {
    public:
        //EntityComponentTreeNode();
        //~EntityComponentTreeNode();
        
        // Entity cache access
        void addEntity(ConstEntityPtr entity);
        bool hasEntity(ConstEntityPtr entity);
        bool removeEntity(ConstEntityPtr entity);
        ConstEntityPtrs getEntities() const;
        
        // System callback access (systems are called internally when entities
        // are added or removed)
        void addSystem(EntitySystem* system);
        void removeSystem(EntitySystem* system);
        
        // Next node access
        // This encapsilates the system of adding an empty node when the deepest
        // part of the tree is reached
        Node getNext(ComponentType type, bool allowCreate = false);
        
    private:
        ConstEntityPtrs entities;
        boost::unordered_set<EntitySystem*> callbacks;
        typedef boost::unordered_map<ComponentType, boost::shared_ptr<EntityComponentTreeNode> > NextNodes;
        NextNodes nextNodes;
    };
    
    // Template functions for EntityManager
    // ------------------------------------
    
	template<class T> boost::shared_ptr<T> EntityManager::addComponent(EntityId entId) {
        EntityPtr entity = getEntity(entId);
        if (entity) {
            return entity->addComponent<T>();
        } else {
            return boost::shared_ptr<T>();
        }
	}
    
    template<class T> bool EntityManager::hasComponent(EntityId entId) const {
        EntityPtr entity = getEntity(entId);
        if (entity) {
            return entity->hasComponent<T>();
        } else {
            return false;
        }
    }
    
    template<class T> boost::shared_ptr<T> EntityManager::getComponent(EntityId entId) const {
        EntityPtr entity = getEntiy(entId);
        if (entity) {
            return entity->getComponent<T>();
        } else {
            return boost::shared_ptr<T>();
        }
    }
    
    template<class T> bool EntityManager::removeComponent() {
        EntityPtr entity = getEntiy(entId);
        if (entity) {
            return entity->removeComponent<T>();
        } else {
            return false;
        }
    }
    
    template<class T> ConstEntityPtrs getEntities() const {
        return getEntities(componentType<T>());
    }
    
}

#endif // header
