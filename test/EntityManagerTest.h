#pragma once
#ifndef idD32D1EA9_0845_4C2F_933A43C672FE41C6
#define idD32D1EA9_0845_4C2F_933A43C672FE41C6

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <gf/EntityManager.h>

class EntityManagerTest : public CppUnit::TestFixture {
public:
    void setUp();
    void tearDown();

    CPPUNIT_TEST_SUITE(EntityManagerTest);
    // Some tests are run in a way that they are order
    // dependent.
    
    // Test creating and destroying an individual
    // entity
    /*CPPUNIT_TEST(entityCreate);
    CPPUNIT_TEST(entityExists);
    CPPUNIT_TEST(entityDestroy);*/
    CPPUNIT_TEST(entity);
    
    // Test adding and removing a single component to a
    // single entity
    /*CPPUNIT_TEST(addComponent);
    CPPUNIT_TEST(hasComponent);
    CPPUNIT_TEST(getComponent);
    CPPUNIT_TEST(removeComponent);*/
    CPPUNIT_TEST(component);
    
    // Test getting the Entity object and accessing
    // components through it
    CPPUNIT_TEST(getEntity);
    
    // Test the multiple variations on getting entities
    // based on their sets of components
    CPPUNIT_TEST(getEntities);
    
    // TODO: Test system callbacks
    CPPUNIT_TEST(registerSystem);
    
    // TODO: Test EntityTemplate creation
    CPPUNIT_TEST(createFromTemplate);
    
    CPPUNIT_TEST_SUITE_END();
    
    /*void entityCreate();
    void entityExists();
    void entityDestroy();*/
    void entity();
    
    /*void addComponent();
    void hasComponent();
    void getComponent();
    void removeComponent();*/
    void component();
    
    void getEntity();
    
    void getEntities();
    
    void registerSystem();
    
    void createFromTemplate();
    
private:
    gf::EntityManager entities;
    
};

#endif // header
