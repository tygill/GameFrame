#include "TestSystem.h"


TestSystem::TestSystem(void) :
        EntitySystem(NULL),
        entitiesReceived(0),
        messagesReceived(0)
{
}


TestSystem::~TestSystem(void) {
}

void TestSystem::added(gf::ConstEntityPtr entity) {
    entitiesReceived++;
}

void TestSystem::removed(gf::ConstEntityPtr entity) {
    entitiesReceived--;
}

void TestSystem::receive(gf::MessagePtr message) {
    messagesReceived++;
}

int TestSystem::entityCount() const {
    return entitiesReceived;
}

int TestSystem::messageCount() const {
    return messagesReceived;
}
