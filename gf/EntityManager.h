#pragma once
#ifndef idAE2BE7B6_9D35_4832_93CD220B7F0597C8
#define idAE2BE7B6_9D35_4832_93CD220B7F0597C8

#include "gf/Global.h"
#include "gf/Entity.h"

namespace gf {
    
    class EntityTemplate;
    
    class EntityManager {
    public:
        EntityManager();
        ~EntityManager();
        
        EntityId create();
        EntityId create(EntityTemplate* form);
        bool exists(EntityId entId) const;
        bool destroy(EntityId entId);
        
        template<class T> boost::shared_ptr<T> addComponent(EntityId entId);
        template<class T> bool hasComponent(EntityId entId) const;
        template<class T> boost::shared_ptr<T> getComponent(EntityId entId) const;
        template<class T> bool removeComponent(EntityId entId);
        
        // Entity access
        // Throws EntityNotFoundException
        Entity entity(EntityId entId) const;
        
        /* T extends EntityComponent */
        template<class T> Entities getEntities() const;
        Entities getEntities(ComponentType type) const;
        Entities getEntities(const ComponentTypes& types) const;

        // One of these functions must be called before getEntities() will return the set of entities with these components.
        // Also note that this must be called at initialization time, before any entities have been created.
        template<class T> void registerEntityCache();
        void registerEntityCache(ComponentType type);
        void registerEntityCache(const ComponentTypes& types);
        
        /*
        template<class T> ConstEntityPtrs getEntities() const;
        ConstEntityPtrs getEntities(ComponentType type) const;
        ConstEntityPtrs getEntities(const ComponentTypes& types) const;
        */
        
        void registerSystem(EntitySystem* system, ComponentType type);
        void registerSystem(EntitySystem* system, const ComponentTypes& types);
        
        // DEBUG
        //void print();
        class EntityComponentTree;

    private:
        // Mutable Entity access is internal only
        EntityPtr getEntity(EntityId entId);
        // EntityPtr access is internal only now too.
        // Returns are only copies.
        ConstEntityPtr getEntity(EntityId entId) const;
        
    private:
        typedef std::set<ComponentType> OrderedComponentTypes;
        typedef boost::unordered_map<EntityId, EntityPtr > EntityMap;
    
        // Set up the EntityComponentTree and Entity classes as other files.
        // Then figure out what this needs to have as member variables.
        //class EntityComponentTree;
        boost::scoped_ptr<EntityComponentTree> components;
        
        EntityMap entities;
    };
    
    
    // EntityManager Helper Classes
    // ----------------------------
    
    class EntityManager::EntityComponentTree {
    public:
        EntityComponentTree();
        ~EntityComponentTree();
        
        // Entity retreval
        ConstEntityPtrs getEntities(ComponentType type) const;
        ConstEntityPtrs getEntities(const EntityManager::OrderedComponentTypes& types) const;

        void registerEntityCache(ComponentType type);
        void registerEntityCache(const EntityManager::OrderedComponentTypes& types);
        
        // Todo: Fix component caching (cache on two factors - add and remove)
        // Component caching management
        void addEntity(ConstEntityPtr entity);
        void addComponent(ConstEntityPtr entity, ComponentType type);
        void removeComponent(ConstEntityPtr entity, ComponentType type);
        //void cacheComponents(ConstEntityPtr entity);
        void removeEntity(ConstEntityPtr entity);
        
        void registerSystem(EntitySystem* system, ComponentType type);
        void registerSystem(EntitySystem* system, const EntityManager::OrderedComponentTypes& types);
        
        // DEBUG
        //void print();
        class EntityComponentTreeNode;

    private:
        //class EntityComponentTreeNode;
        typedef EntityComponentTreeNode* Node;
        
        void addComponent(ConstEntityPtr entity, ComponentType type, const EntityManager::OrderedComponentTypes& types, Node node);
        void cascadeAddComponent(ConstEntityPtr entity, ComponentType type, const EntityManager::OrderedComponentTypes& types, Node node);
        void removeComponent(ConstEntityPtr entity, ComponentType type, const EntityManager::OrderedComponentTypes& types, Node node);
        void cascadeRemoveComponent(ConstEntityPtr entity, ComponentType type, const EntityManager::OrderedComponentTypes& types, Node node);
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
        EntityManager::EntityComponentTree::Node getNext(ComponentType type, bool allowCreate = false);
        
        // DEBUG
        //friend std::ostream& operator<<(std::ostream& out, const EntityManager::EntityComponentTree::EntityComponentTreeNode& node);

    private:
        friend class EntityManager::EntityComponentTree;
        typedef boost::unordered_map<ComponentType, boost::shared_ptr<EntityComponentTreeNode> > NextNodes;
        NextNodes getChildren() const;
        
    private:
        ConstEntityPtrs entities;
        typedef boost::unordered_set<EntitySystem*> WeakEntitySystems;
        WeakEntitySystems callbacks;
        NextNodes nextNodes;
        
    };
    // DEBUG
    //std::ostream& operator<<(std::ostream& out, const EntityManager::EntityComponentTree::EntityComponentTreeNode& node);
    
    // Template functions for EntityManager
    // ------------------------------------
    
	template<class T> boost::shared_ptr<T> EntityManager::addComponent(EntityId entId) {
        EntityPtr entity = getEntity(entId);
        if (entity) {
            boost::shared_ptr<T> ret = entity->addComponent<T>();
            components->addComponent(entity, componentType<T>());
            return ret;
        } else {
            return boost::shared_ptr<T>();
        }
	}
    
    template<class T> bool EntityManager::hasComponent(EntityId entId) const {
        ConstEntityPtr entity = getEntity(entId);
        if (entity) {
            return entity->hasComponent<T>();
        } else {
            return false;
        }
    }
    
    template<class T> boost::shared_ptr<T> EntityManager::getComponent(EntityId entId) const {
        ConstEntityPtr entity = getEntity(entId);
        if (entity) {
            return entity->getComponent<T>();
        } else {
            return boost::shared_ptr<T>();
        }
    }
    
    template<class T> bool EntityManager::removeComponent(EntityId entId) {
        EntityPtr entity = getEntity(entId);
        if (entity) {
            bool ret = entity->removeComponent<T>();
            components->removeComponent(entity, componentType<T>());
            return ret;
        } else {
            return false;
        }
    }
    
    template<class T> Entities EntityManager::getEntities() const {
        return getEntities(componentType<T>());
    }

    template<class T> void EntityManager::registerEntityCache() {
        registerEntityCache(componentType<T>());
    }
    
}

#endif // header
