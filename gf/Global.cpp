#include "gf/Global.h"
// These must be included so that typeid doesn't simply optimize down to the un-virtualized version of the functions!
#include "gf/EntityComponent.h"
#include "gf/Resource.h"
#include "gf/Message.h"

namespace gf {

ComponentType componentType(ComponentPtr comp) {
    return comp->type();
    //return ComponentType(typeid(*comp.get()));
}

ResourceType resourceType(ResourcePtr res) {
    return res->type();
    //return ResourceType(typeid(*res.get()));
}

MessageType messageType(MessagePtr mess) {
    return mess->type();
    //return MessageType(typeid(*mess.get()));
}

}
