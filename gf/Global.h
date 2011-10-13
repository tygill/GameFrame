#pragma once
#ifndef idDAEA559C_E335_4D0C_848F99835A03FB72
#define idDAEA559C_E335_4D0C_848F99835A03FB72

#include <string>
#include <boost/cstdint.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/shared_ptr.hpp>

namespace gf {
    
    // ----------
    // Type Ids
    // ----------
    
    typedef uint32_t EntityId;
    typedef boost::unordered_set<EntityId> EntityIds;
    
    typedef std::type_index ComponentType;
    // For the caching system, a standard set will be used so traversal will
    // be properly ordered
    typedef boost::unordered_set<ComponentType> ComponentTypes;
    
    typedef uint32_t ResourceId;
    typedef boost::unordered_set<ResourceId> ResourceIds;
    typedef std::type_index ResourceType;
    typedef boost::unordered_set<ResourceType> ResourceTypes;
    
    typedef std::type_index MessageType;
    
    // ------------
    // Class sets
    // ------------
    
    // Stored in the EntityManager, and used only to return threadsafe accessors
    // to EntityComponents
    class Entity;
    typedef boost::shared_ptr<Entity> EntityPtr;
    typedef boost::unordered_set<EntityPtr> EntityPtrs;
    typedef boost::shared_ptr<Entity const> ConstEntityPtr;
    typedef boost::unordered_set<ConstEntityPtr> ConstEntityPtrs;
    
    class Resource;
    typedef boost::shared_ptr<Resource> ResourcePtr;
    typedef boost::shared_ptr<Resource const> ConstResourcePtr;
    
    class Message;
    typedef boost::shared_ptr<Message> MessagePtr;
    typedef boost::shared_ptr<Message const> ConstMessagePtr;
    
    class EntitySystem;
    typedef boost::unordered_set<boost::shared_ptr<EntitySystem> > EntitySystems;
    
    template<class T> componentType() {
        return ComponentType(typeid(T));
    }
    
}

#endif // header
