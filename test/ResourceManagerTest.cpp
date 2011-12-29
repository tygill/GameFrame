#include "ResourceManagerTest.h"

#include "DummyResource.h"
#include "DummyResourceTemplate.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ResourceManagerTest);

void ResourceManagerTest::setUp() {
}

void ResourceManagerTest::tearDown() {
}

void ResourceManagerTest::resourceTypeGeneration() {
    // Setup
    gf::ResourcePtr dummy(new DummyResource());

    // Test type comparisons
    //CPPUNIT_ASSERT(dummy->type() != gf::resourceType<gf::Resource>());
    CPPUNIT_ASSERT(dummy->type() == gf::resourceType<DummyResource>());

    // Slightly obsolete method of type checking...but possibly will be kept, as it might prove better in the future.
    // typeid() & RTTI are weird, and replacing it with some sort of global registry might be better....
    CPPUNIT_ASSERT(dummy->type() == gf::resourceType<DummyResource>());
}

void ResourceManagerTest::createResource() {
    // Setup
    gf::ResourceTemplatePtr temp(new DummyResourceTemplate());
    gf::ResourceId res = resources.define<DummyResource>(temp);
    gf::ResourceId res2 = resources.define(gf::resourceType<DummyResource>(), temp);

    boost::shared_ptr<DummyResource const> dummy;

    // Verify that neither resource is loaded yet
    CPPUNIT_ASSERT(!resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(!resources.isLoaded<DummyResource>(res2));
    CPPUNIT_ASSERT(!resources.get<DummyResource>(res));
    CPPUNIT_ASSERT(!resources.get<DummyResource>(res2));

    // Test loading both resources one at a time
    
    resources.load<DummyResource>(res);
    dummy = resources.get<DummyResource>(res);
    CPPUNIT_ASSERT(dummy);
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(!resources.isLoaded<DummyResource>(res2));
    
    resources.load<DummyResource>(res2);
    dummy = resources.get<DummyResource>(res2);
    CPPUNIT_ASSERT(dummy);
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res2));

    resources.load<DummyResource>(res);
    dummy = resources.get<DummyResource>(res);
    CPPUNIT_ASSERT(dummy);
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res2));

    resources.load<DummyResource>(res2);
    dummy = resources.get<DummyResource>(res2);
    CPPUNIT_ASSERT(dummy);
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res2));

    // Begin unloading
    resources.unload<DummyResource>(res);
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res2));
    
    resources.unload<DummyResource>(res2);
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res2));
    
    resources.unload<DummyResource>(res);
    CPPUNIT_ASSERT(!resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(resources.isLoaded<DummyResource>(res2));
    
    resources.unload<DummyResource>(res2);
    CPPUNIT_ASSERT(!resources.isLoaded<DummyResource>(res));
    CPPUNIT_ASSERT(!resources.isLoaded<DummyResource>(res2));

    // Cleanup isn't really required.
}
