#include "gf/EntityManager.h"
#include "gf/EntityTemplate.h"
#include "gf/EntitySystem.h"

namespace gf {

	EntityManager::EntityManager() :
			components(new EntityComponentTree())
	{
		//
	}

	EntityManager::~EntityManager() {
		// Nothing to destroy
	}

	EntityId EntityManager::create() {
	    EntityPtr entity(new Entity());
        entities.insert(std::make_pair(entity->id(), entity));
        components->addEntity(entity);
        return entity->id();
	}

	EntityId EntityManager::create(EntityTemplate* form) {
        // The templates create call must call the standard create() function!!
		return form->create(this);
	}

	bool EntityManager::exists(EntityId entId) const {
		return entities.find(entId) != entities.end();
	}

	bool EntityManager::destroy(EntityId entId) {
        EntityMap::iterator pos = entities.find(entId);
        if (pos != entities.end()) {
            components->removeEntity(pos->second);
            return entities.erase(entId) > 0;
        } else {
            return false;
        }
	}
    
    Entity EntityManager::entity(EntityId entId) const {
        EntityMap::const_iterator pos = entities.find(entId);
        if (pos != entities.end()) {
            return Entity(*pos->second);
        } else {
            throw EntityNotFoundException(entId);
        }
    }
    
    Entities EntityManager::getEntities(ComponentType type) const {
        ConstEntityPtrs ptrs = components->getEntities(type);
        Entities ents;
        for (ConstEntityPtrs::const_iterator itr = ptrs.begin(); itr != ptrs.end(); itr++) {
            ents.insert(Entity(*(*itr)));
        }
        return ents;
    }
    
    Entities EntityManager::getEntities(const ComponentTypes& types) const {
        OrderedComponentTypes orderedTypes(types.begin(), types.end());
        ConstEntityPtrs ptrs = components->getEntities(orderedTypes);
        Entities ents;
        for (ConstEntityPtrs::const_iterator itr = ptrs.begin(); itr != ptrs.end(); itr++) {
            ents.insert(Entity(*(*itr)));
        }
        return ents;
    }

    void EntityManager::registerEntityCache(ComponentType type) {
        components->registerEntityCache(type);
    }

    void EntityManager::registerEntityCache(const ComponentTypes& types) {
        OrderedComponentTypes orderedTypes(types.begin(), types.end());
        components->registerEntityCache(orderedTypes);
    }
    
    void EntityManager::registerSystem(EntitySystem* system, ComponentType type) {
        components->registerSystem(system, type);
    }
    
    void EntityManager::registerSystem(EntitySystem* system, const ComponentTypes& types) {
        OrderedComponentTypes orderedTypes(types.begin(), types.end());
        components->registerSystem(system, orderedTypes);
    }

    // DEBUG
    void EntityManager::print() {
        components->print();
    }
    
    EntityPtr EntityManager::getEntity(EntityId entId) {
        EntityMap::iterator pos = entities.find(entId);
        if (pos != entities.end()) {
            return pos->second;
        } else {
            return EntityPtr();
        }
    }
    
    ConstEntityPtr EntityManager::getEntity(EntityId entId) const {
        EntityMap::const_iterator pos = entities.find(entId);
        if (pos != entities.end()) {
            return pos->second;
        } else {
            return ConstEntityPtr();
        }
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
            ComponentTypes types;
            types.insert(type);
            throw EntitySetNotCachedException(types);
            //return ConstEntityPtrs();
        }
    }
    
    ConstEntityPtrs EntityManager::EntityComponentTree::getEntities(const OrderedComponentTypes& types) const {
        Node node = root.get();
        
        // Iterate down the tree
        for (OrderedComponentTypes::const_iterator itr = types.begin(); itr != types.end(); itr++) {
            node = node->getNext(*itr);
            if (!node) {
                // If we can't go deep enough in the tree to find all the component types,
                // then bail out, as there are no entities
                throw EntitySetNotCachedException(ComponentTypes(types.begin(), types.end()));
                //return ConstEntityPtrs();
            }
        }
        return node->getEntities();
    }

    void EntityManager::EntityComponentTree::registerEntityCache(ComponentType type) {
        // This will create the next node if it can
        root->getNext(type, true);
    }

    void EntityManager::EntityComponentTree::registerEntityCache(const EntityManager::OrderedComponentTypes& types) {
        Node node = root.get();
        
        // Iterate through the tree, adding nodes as needed.
        for (OrderedComponentTypes::const_iterator itr = types.begin(); itr != types.end(); itr++) {
            node = node->getNext(*itr, true);
        }
    }

    void EntityManager::EntityComponentTree::addEntity(ConstEntityPtr entity) {
        root->addEntity(entity);
    }
    
    void EntityManager::EntityComponentTree::addComponent(ConstEntityPtr entity, ComponentType type) {
        // Build the ordered types that would be affected in the tree by adding this type
        ComponentTypes unordered(entity->types()); // 'type' will already be part of the set
        OrderedComponentTypes types(unordered.begin(), unordered.end());
        addComponent(entity, type, types, root.get());
    }
    
    void EntityManager::EntityComponentTree::removeComponent(ConstEntityPtr entity, ComponentType type) {
        // Build the ordered types that would be affected in the tree by adding this type
        ComponentTypes unordered(entity->types()); // 'type' will already be removed from the set
        OrderedComponentTypes types(unordered.begin(), unordered.end());
        removeComponent(entity, type, types, root.get());
    }
    
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

    // DEBUG
    void EntityManager::EntityComponentTree::print() {
        std::cout << *root.get() << std::endl;
    }
    
    void EntityManager::EntityComponentTree::addComponent(ConstEntityPtr entity, ComponentType type, const OrderedComponentTypes& types, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            if (node->hasEntity(entity)) {
                cascadeAddComponent(entity, type, types, node->getNext(type));
                for (OrderedComponentTypes::iterator itr = types.begin(); itr != types.end() && *itr < type; itr++) {
                    Node next = node->getNext(*itr);
                    if (next) {
                        next->addEntity(entity);
                        addComponent(entity, type, types, next);
                    }
                }
            }
        }
    }

    void EntityManager::EntityComponentTree::cascadeAddComponent(ConstEntityPtr entity, ComponentType type, const OrderedComponentTypes& types, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            node->addEntity(entity);
            for (OrderedComponentTypes::reverse_iterator itr = types.rbegin(); itr != types.rend() && *itr > type; itr++) {
                cascadeAddComponent(entity, type, types, node->getNext(*itr));
            }
        }
    }
    
    void EntityManager::EntityComponentTree::removeComponent(ConstEntityPtr entity, ComponentType type, const OrderedComponentTypes& types, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            if (node->hasEntity(entity)) {
                cascadeRemoveComponent(entity, type, types, node->getNext(type));
                for (OrderedComponentTypes::iterator itr = types.begin(); itr != types.end() && *itr < type; itr++) {
                    Node next = node->getNext(*itr);
                    if (next) {
                        removeComponent(entity, type, types, next);
                    }
                }
            }
        }
    }
    
    void EntityManager::EntityComponentTree::cascadeRemoveComponent(ConstEntityPtr entity, ComponentType type, const OrderedComponentTypes& types, EntityManager::EntityComponentTree::Node node) {
        if (node) {
            node->removeEntity(entity);
            for (OrderedComponentTypes::reverse_iterator itr = types.rbegin(); itr != types.rend() && *itr > type; itr++) {
                cascadeRemoveComponent(entity, type, types, node->getNext(*itr));
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
        bool success = entities.insert(entity).second;
        if (success) {
            for (WeakEntitySystems::iterator itr = callbacks.begin(); itr != callbacks.end(); itr++) {
                (*itr)->added(entity);
            }
        }
    }
    
    bool EntityManager::EntityComponentTree::EntityComponentTreeNode::hasEntity(ConstEntityPtr entity) {
        return entities.find(entity) != entities.end();
    }
    
    bool EntityManager::EntityComponentTree::EntityComponentTreeNode::removeEntity(ConstEntityPtr entity) {
        bool success = entities.erase(entity) > 0;
        if (success) {
            for (WeakEntitySystems::iterator itr = callbacks.begin(); itr != callbacks.end(); itr++) {
                (*itr)->added(entity);
            }
        }
        return success;
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
                nextNodes.insert(std::make_pair(type, newNode));
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

    std::ostream& operator<<(std::ostream& out, const EntityManager::EntityComponentTree::EntityComponentTreeNode& node) {
        out << "{\n[";
        bool first = true;
        for (ConstEntityPtrs::const_iterator itr = node.entities.begin(); itr != node.entities.end(); itr++) {
            if (!first) {
                out << ",";
            }
            first = false;
            out << (*itr)->id();
        }
        out << "],\n";
        first = true;
        for (EntityManager::EntityComponentTree::EntityComponentTreeNode::NextNodes::const_iterator itr = node.nextNodes.begin(); itr != node.nextNodes.end(); itr++) {
            if (!first) {
                out << ",\n";
            }
            first = false;
            out << itr->first.name() << ":" << *itr->second.get();
        }
        out << "\n}";
        return out;
    }
    
}
