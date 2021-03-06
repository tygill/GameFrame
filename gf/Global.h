#pragma once
#ifndef idDAEA559C_E335_4D0C_848F99835A03FB72
#define idDAEA559C_E335_4D0C_848F99835A03FB72

#include <string>
#include <set>
#include <map>
// RTTI is being phased out as the provider of message and component type information.
// Static registration is replacing it.
#include <typeindex>
// It appears that gcc doesn't yet support type_index under standard fedora...
// In this case, use this and prefix all typeid() calls with &
//#include <typeinfo>
#include <boost/cstdint.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
//#include <boost/ptr_container.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/chrono.hpp>

// C++11 feature
#ifndef null_ptr
#define null_ptr NULL
#endif

namespace gf {
    
    // ----------
    // Type Ids
    // ----------
    
    typedef uint32_t EntityId;
    typedef boost::unordered_set<EntityId> EntityIds;
    
    typedef uint32_t ComponentType;
//    typedef std::type_index ComponentType;
//    typedef std::type_info* ComponentType;
    // For the caching system, a standard set will be used so traversal will
    // be properly ordered
    typedef boost::unordered_set<ComponentType> ComponentTypes;
    
    typedef uint32_t ResourceId;
    typedef boost::unordered_set<ResourceId> ResourceIds;
    typedef uint32_t ResourceType;
//    typedef std::type_index ResourceType;
//    typedef std::type_info* ResourceType;
    typedef boost::unordered_set<ResourceType> ResourceTypes;
    
    typedef uint32_t MessageType;
    
    // -------
    // Classes
    // -------
    
    class GameFrame;
    class Entity;
    class EntityComponent;
    class Resource;
    class ResourceTemplate;
    class Message;
    class EntitySystem;
    
    // ------------
    // Class sets
    // ------------
    
    // Stored in the EntityManager, and used only to return threadsafe accessors
    // to EntityComponents
    typedef boost::shared_ptr<Entity> EntityPtr;
    typedef boost::unordered_set<EntityPtr> EntityPtrs;
    typedef boost::shared_ptr<Entity const> ConstEntityPtr;
    typedef boost::unordered_set<ConstEntityPtr> ConstEntityPtrs;
    typedef boost::unordered_set<Entity> Entities;

    typedef boost::shared_ptr<EntityComponent> ComponentPtr;
    
    typedef boost::shared_ptr<Resource> ResourcePtr;
    typedef boost::shared_ptr<Resource const> ConstResourcePtr;

    typedef boost::shared_ptr<ResourceTemplate> ResourceTemplatePtr;
    
    typedef boost::shared_ptr<Message> MessagePtr;
    typedef boost::shared_ptr<Message const> ConstMessagePtr;
    
    typedef boost::unordered_set<boost::shared_ptr<EntitySystem> > EntitySystems;
    
    template<class T> ComponentType componentType() {
        return T::staticType();
    }
    
    template<class T> ResourceType resourceType() {
        return T::staticType();
    }

    template<class T> MessageType messageType() {
        return T::staticType();
    }
    
}

#include "gf/Exceptions.h"

#endif // header
