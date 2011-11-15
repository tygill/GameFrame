#include "gf/ResourceManager.h"

namespace gf {
    
    ResourceManager::ResourceManager()
    {
        // Nothing
    }
    
    ResourceManager::~ResourceManager() {
    }
    
    ResourceId ResourceManager::define(ResourceType type, boost::shared_ptr<ResourceTemplate> form) {
        return getTypeManager(type)->define(form);
    }
    
    bool ResourceManager::isLoaded(ResourceType type, ResourceId resId) const {
        ResourceTypeManager const* manager = getTypeManager(type);
        if (manager) {
            return manager->isLoaded(resId);
        } else {
            return false;
        }
    }
    
    void ResourceManager::load(ResourceType type, ResourceId resId) {
        ResourceTypeManager* manager = getTypeManager(type);
        if (manager) {
            manager->load(resId);
        }
    }

    void ResourceManager::unload(ResourceType type, ResourceId resId) {
        ResourceTypeManager* manager = getTypeManager(type);
        if (manager) {
            manager->unload(resId);
        }
    }    
    
    ResourceManager::ResourceTypeManager* ResourceManager::getTypeManager(ResourceType type) {
        TypeManagers::iterator pos = types.find(type);
        if (pos == types.end()) {
            // Create a new type manager
            boost::shared_ptr<ResourceTypeManager> newManager(new ResourceTypeManager);
            std::pair<TypeManagers::iterator, bool> insertPair = types.insert(std::make_pair(type, newManager));
            return insertPair.first->second.get();
        } else {
            return pos->second.get();
        }
    }
    
    ResourceManager::ResourceTypeManager const* ResourceManager::getTypeManager(ResourceType type) const {
        TypeManagers::const_iterator pos = types.find(type);
        if (pos == types.end()) {
            // In the const version, we can't create a new manager
            return null_ptr;
        } else {
            return pos->second.get();
        }
    }
    
    // ResourceManager Helper Classes
    // ------------------------------
    
    // ResourceTypeManager
    // -------------------
    
    ResourceManager::ResourceTypeManager::ResourceTypeManager() :
        nextId(1)
    {
    }
    
    ResourceManager::ResourceTypeManager::~ResourceTypeManager() {
    }
    
    ResourceId ResourceManager::ResourceTypeManager::define(boost::shared_ptr<ResourceTemplate> form) {
        boost::shared_ptr<ResourceMetadata> metadata(new ResourceMetadata(form));
        ResourceId newId = nextId++;
        resources.insert(std::make_pair(newId, metadata));
        return newId;
    }
    
    bool ResourceManager::ResourceTypeManager::isLoaded(ResourceId resId) const {
        Metadatas::const_iterator pos = resources.find(resId);
        if (pos != resources.end()) {
            return pos->second->isLoaded();
        } else {
            return false;
        }
    }
    
    ResourcePtr ResourceManager::ResourceTypeManager::get(ResourceId resId) const {
        Metadatas::const_iterator pos = resources.find(resId);
        if (pos != resources.end()) {
            return pos->second->get();
        } else {
            return ResourcePtr();
        }
    }
    
    void ResourceManager::ResourceTypeManager::load(ResourceId resId) {
        Metadatas::iterator pos = resources.find(resId);
        if (pos != resources.end()) {
            pos->second->load();
        }
    }
    
    void ResourceManager::ResourceTypeManager::unload(ResourceId resId) {
        Metadatas::iterator pos = resources.find(resId);
        if (pos != resources.end()) {
            pos->second->unload();
        }
    }
    
    // ResourceMetadata
    // ----------------
    
    ResourceManager::ResourceTypeManager::ResourceMetadata::ResourceMetadata(boost::shared_ptr<ResourceTemplate> temp) :
        form(temp),
        useCount(0)
    {
    }
    
    ResourceManager::ResourceTypeManager::ResourceMetadata::~ResourceMetadata() {
    }
    
    bool ResourceManager::ResourceTypeManager::ResourceMetadata::isLoaded() const {
        return !!resource;
    }
    
    ResourcePtr ResourceManager::ResourceTypeManager::ResourceMetadata::get() const {
        return resource;
    }
    
    void ResourceManager::ResourceTypeManager::ResourceMetadata::load() {
        if (useCount == 0) {
            ResourcePtr res(form->create());
            resource.swap(res);
        }
        useCount++;
    }
    
    void ResourceManager::ResourceTypeManager::ResourceMetadata::unload() {
        useCount--;
        if (useCount == 0) {
            ResourcePtr res;
            resource.swap(res);
        }
    }
    
}
