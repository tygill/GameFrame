#pragma once
#ifndef id7AF8A304_D2F0_4D43_B157957EA22F00C1
#define id7AF8A304_D2F0_4D43_B157957EA22F00C1

#include "gf/Global.h"
#include "gf/ResourceTemplate.h"

namespace gf {
    
    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();
        
        /* T extends Resource */
        template<class T> ResourceId define(boost::shared_ptr<ResourceTemplate> form);
        
        template<class T> bool isLoaded(ResourceId resId) const;
        // THIS STYLE WAS ABANDONED! See 4 lines down...Get will load the resource on the fly if it is not presently loaded, but will not modify
        // the use count.
        // REMEMBER THIS!! Things may need to be modified to make sure this works right
        // (Though I guess this could just return a null pointer if its unloaded)
        // For now, it will just return null_ptr
        template<class T> boost::shared_ptr<T const> get(ResourceId resId) const;
        
        // Internally, ResourceManager keeps track of how many times load and unload have
        // been called on a particular Resource, and will automatically load and unload
        // from memory when needed.
        // It is possible though that unload will only be marked immediately, and might not
        // be completed until later, in a separate thread for instance.
        template<class T> void load(ResourceId resId);
        template<class T> void unload(ResourceId resId);
        // Preloading will be managed by an independent system, as all it has to do is listen
        // for entities with a new PreloadComponent, and then extract the ResourceType/ResourceId
        // pairs from them, and load them then, in its own thread. It can then send LoadingMessages,
        // which some LoadingDisplaySystem can grab if it wants to show something on screen to
        // indicate the status. Then, when entities lose their PreloadComponent, the ResourceType/
        // ResourceId pairs can again be accessed, and this time used to unload everything.
        
        // All the templated functions map to a function with the ResourceType as the first argument
        // Or at least most of them. These functions are provided so that things like preloaders
        // can preload arbitrary ResourceTypes without compile time knowledge of them.
        // Getting them requires using a templated function though.
        ResourceId define(ResourceType type, ResourceTemplatePtr form);
        bool isLoaded(ResourceType type, ResourceId resId) const;
        void load(ResourceType type, ResourceId resId);
        void unload(ResourceType type, ResourceId resId);
        
    private:
        class ResourceTypeManager;
        
        // Gets the manager for the given type of resources, creating it
        // if one doesn't exist
        ResourceTypeManager* getTypeManager(ResourceType type);
        ResourceTypeManager const* getTypeManager(ResourceType type) const;
        
        typedef boost::unordered_map<ResourceType, boost::shared_ptr<ResourceTypeManager> > TypeManagers;
        TypeManagers types;
    };
    
    class ResourceManager::ResourceTypeManager {
    public:
        ResourceTypeManager();
        ~ResourceTypeManager();
        
        ResourceId define(ResourceTemplatePtr form);
        bool isLoaded(ResourceId resId) const;
        ResourcePtr get(ResourceId resId) const;
        void load(ResourceId resId);
        void unload(ResourceId resId);
        
    private:
        class ResourceMetadata;
        typedef boost::unordered_map<ResourceId, boost::shared_ptr<ResourceMetadata> > Metadatas;
        Metadatas resources;
        
        ResourceId nextId;
    };
    
    class ResourceManager::ResourceTypeManager::ResourceMetadata {
    public:
        ResourceMetadata(ResourceTemplatePtr temp);
        ~ResourceMetadata();
        
        bool isLoaded() const;
        ResourcePtr get() const;
        void load();
        void unload();
        
    private:
        // This stores the template to (re)build the Resource when it is loaded.
        ResourceTemplatePtr form;
        // Load count (independent from shared_ptr count - this way, if something else is still
        // holding on to the Resource via some pointer somewhere, the program won't crash, but the
        // ResourceManager will simply let go of its copy, so that the moment the other holder of
        // the Resource lets go, it will be destroyed.)
        uint64_t useCount;
        // The actual, cached resource. Swapped to NULL when not loaded.
        // Here, this shared_ptr<Resource> is dynamically castable to
        // shared_ptr<ResourceType>, which allows one hard coded class to function
        // as a cache for any type of user defined Resource.
        ResourcePtr resource;
    };
    
    // Template Implementations
    
    // ResourceManager
    // ---------------
    
    template<class T> ResourceId ResourceManager::define(boost::shared_ptr<ResourceTemplate> form) {
        return define(resourceType<T>(), form);
    }

    template<class T> bool ResourceManager::isLoaded(ResourceId resId) const {
        return isLoaded(resourceType<T>(), resId);
    }
    
    template<class T> boost::shared_ptr<T const> ResourceManager::get(ResourceId resId) const {
        ResourceTypeManager const* manager = getTypeManager(resourceType<T>());
        if (manager) {
            // dynamic cast could probably work too, but this is
            // faster, and should never have issues anyway.
            return boost::static_pointer_cast<T const>(manager->get(resId));
        } else {
            throw ResourceNotFoundException(resourceType<T>(), resId);
            //return boost::shared_ptr<T const>();
        }
    }
    
    template<class T> void ResourceManager::load(ResourceId resId) {
        load(resourceType<T>(), resId);
    }
    
    template<class T> void ResourceManager::unload(ResourceId resId) {
        unload(resourceType<T>(), resId);
    }
    
}

#endif // header
