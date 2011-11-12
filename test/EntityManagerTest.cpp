#include "EntityManagerTest.h"

#include "TestSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "DummyComponent.h"

CPPUNIT_TEST_SUITE_REGISTRATION(EntityManagerTest);

void EntityManagerTest::setUp() {
    // Nothing
    entities.registerEntityCache<PositionComponent>();
    entities.registerEntityCache<VelocityComponent>();
    gf::ComponentTypes types;
    types.insert(gf::componentType<PositionComponent>());
    types.insert(gf::componentType<VelocityComponent>());
    entities.registerEntityCache(types);
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
    pos->setX(10.0);
    CPPUNIT_ASSERT(pos->x() == 10.0);
    
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
    pos->setX(10.0);
    boost::shared_ptr<VelocityComponent> vel = entities.addComponent<VelocityComponent>(ent);
    vel->setVelocity(10.0);
    
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

void EntityManagerTest::registerEntityCache() {
    // Setup
    // We already know that Position, Velocity, and Position+Velocity sets are registered,
    // and that DummyComponent is not registered for anything.

    gf::EntityId ent = entities.create();
    auto pos = entities.addComponent<PositionComponent>(ent);
    auto vel = entities.addComponent<VelocityComponent>(ent);
    auto dum = entities.addComponent<DummyComponent>(ent);

    gf::EntityId ent2 = entities.create();
    auto pos2 = entities.addComponent<PositionComponent>(ent2);
    auto vel2 = entities.addComponent<VelocityComponent>(ent2);
    auto dum2 = entities.addComponent<DummyComponent>(ent2);

    // Test templated access to entity cache
    CPPUNIT_ASSERT(entities.getEntities<PositionComponent>().size() == 2);
    CPPUNIT_ASSERT(entities.getEntities<VelocityComponent>().size() == 2);
    CPPUNIT_ASSERT_THROW(entities.getEntities<DummyComponent>(), gf::EntitySetNotCachedException);

    // Test single component access
    CPPUNIT_ASSERT(entities.getEntities(gf::componentType<PositionComponent>()).size() == 2);
    CPPUNIT_ASSERT(entities.getEntities(gf::componentType<VelocityComponent>()).size() == 2);
    CPPUNIT_ASSERT_THROW(entities.getEntities(gf::componentType<DummyComponent>()), gf::EntitySetNotCachedException);

    // Test component set access
    gf::ComponentTypes types;

    types.insert(gf::componentType<PositionComponent>());
    CPPUNIT_ASSERT(entities.getEntities(types).size() == 2);
    types.clear();

    types.insert(gf::componentType<VelocityComponent>());
    CPPUNIT_ASSERT(entities.getEntities(types).size() == 2);
    types.clear();

    types.insert(gf::componentType<DummyComponent>());
    CPPUNIT_ASSERT_THROW(entities.getEntities(types), gf::EntitySetNotCachedException);
    types.clear();
    
    types.insert(gf::componentType<PositionComponent>());
    types.insert(gf::componentType<VelocityComponent>());
    CPPUNIT_ASSERT(entities.getEntities(types).size() == 2);
    types.clear();
    
    types.insert(gf::componentType<PositionComponent>());
    types.insert(gf::componentType<DummyComponent>());
    CPPUNIT_ASSERT_THROW(entities.getEntities(types), gf::EntitySetNotCachedException);
    types.clear();
    
    types.insert(gf::componentType<VelocityComponent>());
    types.insert(gf::componentType<DummyComponent>());
    CPPUNIT_ASSERT_THROW(entities.getEntities(types), gf::EntitySetNotCachedException);
    types.clear();
    
    types.insert(gf::componentType<PositionComponent>());
    types.insert(gf::componentType<VelocityComponent>());
    types.insert(gf::componentType<DummyComponent>());
    CPPUNIT_ASSERT_THROW(entities.getEntities(types), gf::EntitySetNotCachedException);
    types.clear();
    
    // Clean up
    entities.destroy(ent);
    entities.destroy(ent2);
}

void EntityManagerTest::getEntities() {
    // Setup
    gf::EntityId ent = entities.create();
    boost::shared_ptr<PositionComponent> pos = entities.addComponent<PositionComponent>(ent);
    boost::shared_ptr<VelocityComponent> vel = entities.addComponent<VelocityComponent>(ent);
    
    gf::EntityId ent2 = entities.create();
    boost::shared_ptr<PositionComponent> pos2 = entities.addComponent<PositionComponent>(ent2);
    // Make sure it works for when components are removed as well
    boost::shared_ptr<VelocityComponent> vel2 = entities.addComponent<VelocityComponent>(ent2);
    entities.removeComponent<VelocityComponent>(ent2);

    gf::EntityId ent3 = entities.create();
    boost::shared_ptr<PositionComponent> pos3 = entities.addComponent<PositionComponent>(ent3);
    entities.removeComponent<PositionComponent>(ent3);
    boost::shared_ptr<VelocityComponent> vel3 = entities.addComponent<VelocityComponent>(ent3);

    // Make sure order of the components doesn't matter
    gf::EntityId ent4 = entities.create();
    boost::shared_ptr<VelocityComponent> vel4 = entities.addComponent<VelocityComponent>(ent4);
    boost::shared_ptr<PositionComponent> pos4 = entities.addComponent<PositionComponent>(ent4);

    // Check getting the entities by all three methods
    {
        gf::Entities ents = entities.getEntities<PositionComponent>();
        CPPUNIT_ASSERT(ents.size() == 3);
        for (gf::Entities::iterator itr = ents.begin(); itr != ents.end(); itr++) {
            CPPUNIT_ASSERT((itr->id() == ent || itr->id() == ent2 || itr->id() == ent4) && itr->id() != ent3);
        }

        gf::Entities ents2 = entities.getEntities(gf::componentType<PositionComponent>());
        CPPUNIT_ASSERT(ents2.size() == 3);
        for (gf::Entities::iterator itr = ents2.begin(); itr != ents2.end(); itr++) {
            CPPUNIT_ASSERT((itr->id() == ent || itr->id() == ent2 || itr->id() == ent4) && itr->id() != ent3);
        }

        gf::ComponentTypes types;
        types.insert(gf::componentType<PositionComponent>());
        gf::Entities ents3 = entities.getEntities(types);
        CPPUNIT_ASSERT(ents3.size() == 3);
        for (gf::Entities::iterator itr = ents3.begin(); itr != ents3.end(); itr++) {
            CPPUNIT_ASSERT((itr->id() == ent || itr->id() == ent2 || itr->id() == ent4) && itr->id() != ent3);
        }
    }

    // Check getting the other component's entities
    {
        gf::Entities ents = entities.getEntities<VelocityComponent>();
        CPPUNIT_ASSERT(ents.size() == 3);
        for (gf::Entities::iterator itr = ents.begin(); itr != ents.end(); itr++) {
            CPPUNIT_ASSERT((itr->id() == ent || itr->id() == ent3 || itr->id() == ent4) && itr->id() != ent2);
        }

        gf::Entities ents2 = entities.getEntities(gf::componentType<VelocityComponent>());
        CPPUNIT_ASSERT(ents2.size() == 3);
        for (gf::Entities::iterator itr = ents2.begin(); itr != ents2.end(); itr++) {
            CPPUNIT_ASSERT((itr->id() == ent || itr->id() == ent3 || itr->id() == ent4) && itr->id() != ent2);
        }

        gf::ComponentTypes types;
        types.insert(gf::componentType<VelocityComponent>());
        gf::Entities ents3 = entities.getEntities(types);
        CPPUNIT_ASSERT(ents3.size() == 3);
        for (gf::Entities::iterator itr = ents3.begin(); itr != ents3.end(); itr++) {
            CPPUNIT_ASSERT((itr->id() == ent || itr->id() == ent3 || itr->id() == ent4) && itr->id() != ent2);
        }
    }

    // Check getting entities with both components
    {
        gf::ComponentTypes types;
        types.insert(gf::componentType<PositionComponent>());
        types.insert(gf::componentType<VelocityComponent>());
        gf::Entities ents = entities.getEntities(types);
        CPPUNIT_ASSERT(ents.size() == 2);
        for (gf::Entities::iterator itr = ents.begin(); itr != ents.end(); itr++) {
            CPPUNIT_ASSERT(itr->id() == ent || itr->id() == ent4);
        }
    }

    // Test getting all entities (empty types list)
    {
        gf::ComponentTypes types;
        gf::Entities ents = entities.getEntities(types);
        CPPUNIT_ASSERT(ents.size() == 4);
        for (gf::Entities::iterator itr = ents.begin(); itr != ents.end(); itr++) {
            CPPUNIT_ASSERT(itr->id() == ent || itr->id() == ent2 || itr->id() == ent3 || itr->id() == ent4);
        }
    }

    // Clean up
    entities.destroy(ent);
    entities.destroy(ent2);
    entities.destroy(ent3);
    entities.destroy(ent4);

    // Make sure all the components were cleaned up when the entities were destroyed
    {
        gf::Entities ents = entities.getEntities<VelocityComponent>();
        CPPUNIT_ASSERT(ents.size() == 0);

        gf::Entities ents2 = entities.getEntities<PositionComponent>();
        CPPUNIT_ASSERT(ents2.size() == 0);

        gf::ComponentTypes types;
        types.insert(gf::componentType<PositionComponent>());
        types.insert(gf::componentType<VelocityComponent>());
        gf::Entities ents4 = entities.getEntities(types);
        CPPUNIT_ASSERT(ents4.size() == 0);
    }
}

void EntityManagerTest::registerSystem() {
    // Setup
    TestSystem positionSystem;
    TestSystem bothSystem;
    entities.registerSystem(&positionSystem, gf::componentType<PositionComponent>());
    gf::ComponentTypes types;
    types.insert(gf::componentType<PositionComponent>());
    types.insert(gf::componentType<VelocityComponent>());
    entities.registerSystem(&bothSystem, types);

    // Test the single system and combined system
    CPPUNIT_ASSERT(positionSystem.entityCount() == 0);
    CPPUNIT_ASSERT(bothSystem.entityCount() == 0);

    gf::EntityId ent = entities.create();
    entities.addComponent<PositionComponent>(ent);

    CPPUNIT_ASSERT(positionSystem.entityCount() == 1);
    CPPUNIT_ASSERT(bothSystem.entityCount() == 0);

    entities.addComponent<VelocityComponent>(ent);
    
    CPPUNIT_ASSERT(positionSystem.entityCount() == 1);
    CPPUNIT_ASSERT(bothSystem.entityCount() == 1);

    gf::EntityId ent2 = entities.create();
    entities.addComponent<VelocityComponent>(ent2);
    
    CPPUNIT_ASSERT(positionSystem.entityCount() == 1);
    CPPUNIT_ASSERT(bothSystem.entityCount() == 1);

    entities.addComponent<PositionComponent>(ent2);

    CPPUNIT_ASSERT(positionSystem.entityCount() == 2);
    CPPUNIT_ASSERT(bothSystem.entityCount() == 2);

    // Clean up
    entities.destroy(ent);
    entities.destroy(ent2);
}

void EntityManagerTest::createFromTemplate() {
}
