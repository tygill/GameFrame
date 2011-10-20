#include "gf/EntityManager.h"
#include "gf/EntityTemplate.h"

namespace gf {

	EntityManager::EntityManager() :
			components(new EntityComponentTree()),
			nextId(1)
	{
		//
	}

	EntityManager::~EntityManager() {
		// Nothing to destroy
	}

	EntityId EntityManager::create() {
		EntityId entId = nextId;
	    EntityPtr entity(new Entity());
	    bool success = entities.insert(std::pair<EntityId, EntityPtr>(entId, entity)).second;
	    while (!success) {
	        entId++;
	        success = entities.insert(std::pair<EntityId, EntityPtr>(entId, entity)).second;
	    }
	    nextId = entId + 1;
	    return entId;
	}

	EntityId EntityManager::create(EntityTemplate* form) {
		return form->create(this);
	}

	bool EntityManager::exists(EntityId entId) const {
		return entities.find(entId) != entities.end();
	}

	bool EntityManager::destroy(EntityId entId) {
		return entities.erase(entId) > 0;
	}
    
    ConstEntityPtr EntityManager::getEntity(EntityId entId) const {
        return getEntity(entId);
    }
    
    ConstEntityPtrs EntityManager::getEntities(ComponentType type) const {
        return components->getEntities(type);
    }
    
    ConstEntityPtrs EntityManager::getEntities(const ComponentTypes& types) const {
        OrderedComponentTypes orderedTypes(types.begin(), types.end());
        return components->getEntities(orderedTypes);
    }
    
    void EntityManager::registerSystem(EntitySystem* system, ComponentType type) {
        components->registerSystem(system, type);
    }
    
    void EntityManager::registerSystem(EntitySystem* system, const ComponentTypes& types) {
        OrderedComponentTypes orderedTypes(types.begin(), types.end());
        components->registerSystem(system, orderedTypes);
    }
    
    
    // EntityManager Helper Classes
    // ----------------------------
    
    // EntityManager::EntityComponentTree
    // ----------------------------------
    
    EntityManager::EntityComponentTree::EntityComponentTree() :
        root(new EntityManager::EntityComponentTree::EntityComponentTreeNode())
    {
        // Nothing else to create
    }
    
    EntityManager::EntityComponentTree::~EntityComponentTree() {
        // Nothing to destroy
    }
    
    ConstEntityPtrs EntityManager::EntityComponentTree::getEntities(ComponentType type) const {
        Node node = root->getNext(type);
        if (node) {
            return node->getEntities();
        } else {
            return ConstEntityPtrs();
        }
    }
    
    ConstEntityPtrs EntityManager::EntityComponentTree::getEntities(const OrderedComponentTypes& types) const {
        Node node = root.get();
        
        // Iterate down the tree
        for (OrderedComponentTypes::const_iterator itr = types.begin(); itr != types.end(); itr++) {
            node = node->getNext(*itr);
            if (node) {
                // If we can't go deep enough in the tree to find all the component types,
                // then bail out, as there are no entities
                return ConstEntityPtrs();
            }
        }
        return node->getEntities();
    }
    
    void EntityManager::EntityComponentTree::addComponent(ConstEntityPtr entity, ComponentType type) {
        // Build the ordered types that would be affected in the tree by adding
        // this type
        ComponentTypes unordered(entity->getTypes());
        OrderedComponentTypes types;
        for (ComponentTypes::const_iterator itr = unordered.begin(); itr != unordered.end() && *itr < type; itr++) {
            types.insert(*itr);
        }
        addComponent(entity, type, types, root.get());
    }
    
    void EntityManager::EntityComponentTree::removeComponent(ConstEntityPtr entity, ComponentType type) {
        // Build the ordered types that would be affected in the tree by adding
        // this type
        ComponentTypes unordered(entity->getTypes());
        OrderedComponentTypes types;
        for (ComponentTypes::const_iterator itr = unordered.begin(); itr != unordered.end() && *itr < type; itr++) {
            types.insert(*itr);
        }
        removeComponent(entity, type, types, root.get());
    }
    
    /*
    void EntityManager::EntityComponentTree::cacheComponents(ConstEntityPtr entity) {
        OrderedComponentTypes ordered(entity->getTypes().begin(), entity->getTypes().end());
        cacheComponents(entity, ordered, root);
    }
    */
    
    void EntityManager::EntityComponentTree::removeEntity(ConstEntityPtr entity) {
        removeEntity(entity, root.get());
    }
    
    void EntityManager::EntityComponentTree::registerSystem(EntitySystem* system, ComponentType type) {
        root->getNext(type, true)->addSystem(system);
    }
    
    void EntityManager::EntityComponentTree::registerSystem(EntitySystem* system, const OrderedComponentTypes& types) {
        Node node = root.get();
        for (OrderedComponentTypes::const_iterator itr = types.begin(); itr != types.end(); itr++) {
            // true as the second parameter forces getNext to create a new node if one doesn't
            // already exist
            node = node->getNext(*itr, true);
        }
        node->addSystem(system);
    }
    
    void EntityManager::EntityComponentTree::addComponent(ConstEntityPtr entity, ComponentType type, OrderedComponentTypes& types, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            if (node->hasEntity(entity)) {
                node->getNext(type, true)->addEntity(entity);
                OrderedComponentTypes typesCopy(types);
                for (OrderedComponentTypes::const_iterator itr = typesCopy.begin(); itr != typesCopy.end(); itr++) {
                    types.erase(*itr);
                    addComponent(entity, type, types, node->getNext(*itr));
                    types.insert(*itr);
                }
            }
        }
    }
    
    void EntityManager::EntityComponentTree::removeComponent(ConstEntityPtr entity, ComponentType type, OrderedComponentTypes& types, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            if (node->hasEntity(entity)) {
                node->getNext(type, true)->removeEntity(entity);
                OrderedComponentTypes typesCopy(types);
                for (OrderedComponentTypes::const_iterator itr = typesCopy.begin(); itr != typesCopy.end(); itr++) {
                    types.erase(*itr);
                    removeComponent(entity, type, types, node->getNext(*itr));
                    types.insert(*itr);
                }
            }
        }
    }
    
    /*
    void EntityManager::EntityComponentTree::cacheComponents(ConstEntityPtr entity, OrderedComponentTypes& types, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            node->addEntity(entId);
            if (types.size() > 0) {
                ComponentType type = *types.begin();
                types.erase(type);
                cacheComponents(entity, types, node->getNext(type, true));
                types.insert(type);
            } else {
                for (ConstEntityPtrs::const_iterator itr = node->getEntities().begin(); itr != node->getEntites().end(); itr++) {
                    removeEntity(entity, *itr);
                }
            }
        }
    }
    */
    
    void EntityManager::EntityComponentTree::removeEntity(ConstEntityPtr entity, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            if (node->removeEntity(entity)) {
                EntityComponentTreeNode::NextNodes nodes(node->getChildren());
                for (EntityComponentTreeNode::NextNodes::const_iterator itr = nodes.begin(); itr != nodes.end(); itr++) {
                    removeEntity(entity, itr->second.get());
                }
            }
        }
    }
    
    
    // EntityManager::EntityComponentTree::EntityComponentTreeNode
    // -----------------------------------------------------------
    
    void EntityManager::EntityComponentTree::EntityComponentTreeNode::addEntity(ConstEntityPtr entity) {
        entities.insert(entity);
    }
    
    bool EntityManager::EntityComponentTree::EntityComponentTreeNode::hasEntity(ConstEntityPtr entity) {
        return entities.find(entity) != entities.end();
    }
    
    bool EntityManager::EntityComponentTree::EntityComponentTreeNode::removeEntity(ConstEntityPtr entity) {
        return entities.erase(entity) > 0;
    }
    
    ConstEntityPtrs EntityManager::EntityComponentTree::EntityComponentTreeNode::getEntities() const {
        return entities;
    }
    
    void EntityManager::EntityComponentTree::EntityComponentTreeNode::addSystem(EntitySystem* system) {
        callbacks.insert(system);
    }
    
    void EntityManager::EntityComponentTree::EntityComponentTreeNode::removeSystem(EntitySystem* system) {
        callbacks.erase(system);
    }
    
    EntityManager::EntityComponentTree::Node EntityManager::EntityComponentTree::EntityComponentTreeNode::getNext(ComponentType type, bool allowCreate) {
        NextNodes::iterator pos = nextNodes.find(type);
        Node node = null_ptr;
        if (pos == nextNodes.end()) {
            if (allowCreate) {
                boost::shared_ptr<EntityComponentTreeNode> newNode(new EntityComponentTreeNode());
                nextNodes.insert(std::pair<ComponentType, boost::shared_ptr<EntityComponentTreeNode> >(type, newNode));
                node = newNode.get();
            }
        } else {
            node = pos->second.get();
        }
        return node;
    }
    
    EntityManager::EntityComponentTree::EntityComponentTreeNode::NextNodes EntityManager::EntityComponentTree::EntityComponentTreeNode::getChildren() const {
        return nextNodes;
    }
    
}
