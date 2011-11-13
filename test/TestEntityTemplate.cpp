#include "TestEntityTemplate.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

gf::EntityId TestEntityTemplate::create(gf::EntityManager* manager) {
    gf::EntityId ent = manager->create();
    boost::shared_ptr<PositionComponent> pos = manager->addComponent<PositionComponent>(ent);
    pos->setX(10);
    pos->setY(10);
    boost::shared_ptr<VelocityComponent> vel = manager->addComponent<VelocityComponent>(ent);
    vel->setVelocity(5);
    vel->setDirection(2);
    return ent;
}
