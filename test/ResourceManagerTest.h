#pragma once
#ifndef id6266B07C_642E_48DE_A1C5D48E91AE7DF1
#define id6266B07C_642E_48DE_A1C5D48E91AE7DF1

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <gf/ResourceManager.h>

class ResourceManagerTest : public CppUnit::TestFixture {
public:
    void setUp();
    void tearDown();
    
    CPPUNIT_TEST_SUITE(ResourceManagerTest);

    CPPUNIT_TEST(resourceTypeGeneration);
    CPPUNIT_TEST(createResource);
    
    CPPUNIT_TEST_SUITE_END();
    
    void resourceTypeGeneration();
    void createResource();

private:
    gf::ResourceManager resources;

};

#endif // header
