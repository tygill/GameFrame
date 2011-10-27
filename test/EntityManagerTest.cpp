#include "EntityManagerTest.h"

#include "PositionComponent.h"
#include "VelocityComponent.h"

CPPUNIT_TEST_SUITE_REGISTRATION(EntityManagerTest);

void EntityManagerTest::setUp() {
    // Nothing
}

void EntityManagerTest::tearDown() {
    // Nothing
}

void EntityManagerTest::entity() {
    gf::EntityId ent = entities.create();
    CPPUNIT_ASSERT(ent != 0);
    CPPUNIT_ASSERT(entities.exists(ent));
    
    // Test creating a second entity, and make sure the id is different
    gf::EntityId ent2 = entities.create();
    CPPUNIT_ASSERT(ent2 != 0);
    CPPUNIT_ASSERT(entities.exists(ent2));
    CPPUNIT_ASSERT(ent != ent2);
    
    CPPUNIT_ASSERT(entities.destroy(ent));
    // Make sure it was really destroyed
    CPPUNIT_ASSERT(!entities.exists(ent));
    // Make sure the other one wasn't destroyed
    CPPUNIT_ASSERT(entities.exists(ent2));
    // Destroy the second one
    CPPUNIT_ASSERT(entities.destroy(ent2));
    // Make sure destroy returns a proper boolean for a failed destroy
    CPPUNIT_ASSERT(!entities.destroy(ent));
}

void EntityManagerTest::component() {
    gf::EntityId ent = entities.create();
    CPPUNIT_ASSERT(!entities.hasComponent<PositionComponent>(ent));
    CPPUNIT_ASSERT(!entities.hasComponent<VelocityComponent>(ent));
    // Check retrieval of non-existant component
    boost::shared_ptr<PositionComponent> pos = entities.getComponent<PositionComponent>(ent);
    CPPUNIT_ASSERT(!pos);
    boost::shared_ptr<VelocityComponent> vel = entities.getComponent<VelocityComponent>(ent);
    CPPUNIT_ASSERT(!vel);
    // Check adding a component
    pos = entities.addComponent<PositionComponent>(ent);
    CPPUNIT_ASSERT(pos);
    CPPUNIT_ASSERT(entities.hasComponent<PositionComponent>(ent));
    CPPUNIT_ASSERT(!entities.hasComponent<VelocityComponent>(ent));
    CPPUNIT_ASSERT(!entities.getComponent<VelocityComponent>(ent));
    pos->setX(10.0d);
    CPPUNIT_ASSERT(pos->x() == 10.0d);
    
    boost::shared_ptr<PositionComponent> pos2 = entities.addComponent<PositionComponent>(ent);
    CPPUNIT_ASSERT(pos == pos2);
    CPPUNIT_ASSERT(pos->x() == pos2->x());
    
    boost::shared_ptr<PositionComponent> pos3 = entities.getComponent<PositionComponent>(ent);
    CPPUNIT_ASSERT(pos == pos3);
    CPPUNIT_ASSERT(pos->x() == pos3->x());
    
    vel = entities.addComponent<VelocityComponent>(ent);
    CPPUNIT_ASSERT(vel);
    CPPUNIT_ASSERT(entities.hasComponent<VelocityComponent>(ent));
    CPPUNIT_ASSERT(entities.hasComponent<PositionComponent>(ent));
    
    // Test removing components
    CPPUNIT_ASSERT(entities.removeComponent<PositionComponent>(ent));
    CPPUNIT_ASSERT(!entities.hasComponent<PositionComponent>(ent));
    CPPUNIT_ASSERT(entities.hasComponent<VelocityComponent>(ent));
    CPPUNIT_ASSERT(!entities.removeComponent<PositionComponent>(ent));
    
    CPPUNIT_ASSERT(entities.removeComponent<VelocityComponent>(ent));
    CPPUNIT_ASSERT(!entities.hasComponent<VelocityComponent>(ent));
    
    // Remove this component
    CPPUNIT_ASSERT(entities.destroy(ent));
}

void EntityManagerTest::getEntity() {
    // Setup
    gf::EntityId ent = entities.create();
    boost::shared_ptr<PositionComponent> pos = entities.addComponent<PositionComponent>(ent);
    pos->setX(10.0d);
    boost::shared_ptr<VelocityComponent> vel = entities.addComponent<VelocityComponent>(ent);
    vel->setVelocity(10.0d);
    
    // Get the entity, and make sure the components we already got are the same as the ones we already saved
    gf::Entity entity = entities.entity(ent);
    CPPUNIT_ASSERT(entity.id() == ent);
    
    CPPUNIT_ASSERT(entity.hasComponent<PositionComponent>());
    CPPUNIT_ASSERT(entity.getComponent<PositionComponent>() == pos);
    CPPUNIT_ASSERT(entity.getComponent<PositionComponent>()->x() == pos->x());
    CPPUNIT_ASSERT(entity.getComponent<PositionComponent>()->y() == pos->y());
    
    CPPUNIT_ASSERT(entity.hasComponent<VelocityComponent>());
    CPPUNIT_ASSERT(entity.getComponent<VelocityComponent>() == vel);
    CPPUNIT_ASSERT(entity.getComponent<VelocityComponent>()->velocity() == vel->velocity());
    CPPUNIT_ASSERT(entity.getComponent<VelocityComponent>()->direction() == vel->direction());
    
    // Remove the components from the core model
    CPPUNIT_ASSERT(entities.removeComponent<PositionComponent>(ent));
    CPPUNIT_ASSERT(entities.removeComponent<VelocityComponent>(ent));
    
    // Make sure the Entity still holds a valid copy of the components
    CPPUNIT_ASSERT(entity.hasComponent<PositionComponent>());
    CPPUNIT_ASSERT(entity.getComponent<PositionComponent>() == pos);
    CPPUNIT_ASSERT(entity.getComponent<PositionComponent>()->x() == pos->x());
    CPPUNIT_ASSERT(entity.getComponent<PositionComponent>()->y() == pos->y());
    
    CPPUNIT_ASSERT(entity.hasComponent<VelocityComponent>());
    CPPUNIT_ASSERT(entity.getComponent<VelocityComponent>() == vel);
    CPPUNIT_ASSERT(entity.getComponent<VelocityComponent>()->velocity() == vel->velocity());
    CPPUNIT_ASSERT(entity.getComponent<VelocityComponent>()->direction() == vel->direction());
    
    // Clean up
    CPPUNIT_ASSERT(entities.destroy(ent));
    
    // Make sure getting a non existant entity throws an EntityNotFound exception
    CPPUNIT_ASSERT_THROW(entities.entity(ent), gf::EntityNotFoundException);
}

void EntityManagerTest::getEntities() {
}

void EntityManagerTest::registerSystem() {
}

void EntityManagerTest::createFromTemplate() {
}
