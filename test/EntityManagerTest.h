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
    
    // Test creating and destroying an individual
    // entity
    CPPUNIT_TEST(entity);
    
    // Test adding and removing a single component to a
    // single entity
    CPPUNIT_TEST(component);
    
    // Test getting the Entity object and accessing
    // components through it
    CPPUNIT_TEST(getEntity);
    
    // Test entity cache registration, and verify that
    // getEntities of non-registered entities throws an
    // exception
    CPPUNIT_TEST(registerEntityCache);
    
    // Test the multiple variations on getting entities
    // based on their sets of components
    CPPUNIT_TEST(getEntities);

    // Test system callbacks
    CPPUNIT_TEST(registerSystem);
    
    // TODO: Test EntityTemplate creation
    CPPUNIT_TEST(createFromTemplate);
    
    CPPUNIT_TEST_SUITE_END();
    
    void entity();
    
    void component();
    
    void getEntity();
    
    void registerEntityCache();

    void getEntities();
    
    void registerSystem();
    
    void createFromTemplate();
    
private:
    gf::EntityManager entities;
    
};

#endif // header
