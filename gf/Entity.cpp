#include "gf/Entity.h"

namespace gf {
    
    EntityId Entity::nextId = 1;
    
    Entity::Entity() :
        entId(nextId++)
    {
        // Eventually, this should probably do some sort of id management so
        // wrap around doesn't cause issues.
    }
    
    Entity::Entity(const Entity& other) :
        componentTypes(other.componentTypes),
        components(other.components),
        entId(other.entId)
    {
    }
    
    Entity::~Entity() {
    }
    
    bool Entity::operator==(const Entity& other) const {
        return entId == other.entId;
    }
    
    ComponentTypes Entity::types() const {
        return componentTypes;
    }
    
    void Entity::setId(EntityId newId) {
        entId = newId;
    }
    
    EntityId Entity::id() const {
        return entId;
    }
    
    std::size_t hash_value(const Entity& ent) {
        boost::hash<int> hasher;
        return hasher(ent.id());
    }
    
}
