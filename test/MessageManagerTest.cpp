#include "MessageManagerTest.h"

#include "DummyMessage.h"
#include "EmptyMessage.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MessageManagerTest);

void MessageManagerTest::setUp() {
    messages.registerSystem(&system, gf::messageType<EmptyMessage>());
}

void MessageManagerTest::tearDown() {
}

void MessageManagerTest::messageTypeGeneration() {
    // Setup
    gf::MessagePtr empty(new EmptyMessage());
    gf::MessagePtr dummy(new DummyMessage());

    // Test type comparisons
    CPPUNIT_ASSERT(gf::messageType(empty) != gf::messageType<gf::Message>());
    CPPUNIT_ASSERT(gf::messageType(dummy) != gf::messageType<gf::Message>());
    CPPUNIT_ASSERT(empty->type() == gf::messageType<EmptyMessage>());
    CPPUNIT_ASSERT(dummy->type() == gf::messageType<DummyMessage>());

    // Slightly obsolete method of type checking...but possibly will be kept, as it might prove better in the future.
    // typeid() & RTTI are weird, and replacing it with some sort of global registry might be better....
    CPPUNIT_ASSERT(gf::messageType(empty) == gf::messageType<EmptyMessage>());
    CPPUNIT_ASSERT(gf::messageType(dummy) == gf::messageType<DummyMessage>());
}

void MessageManagerTest::sendMessage() {
    // Setup
    gf::MessagePtr empty(new EmptyMessage());
    gf::MessagePtr dummy(new DummyMessage());

    // Test presumption
    CPPUNIT_ASSERT(system.messageCount() == 0);
    
    // Test sending via template
    messages.send<EmptyMessage>();
    CPPUNIT_ASSERT(system.messageCount() == 1);
    
    // Test sending unregistered message
    messages.send<DummyMessage>();
    CPPUNIT_ASSERT(system.messageCount() == 1);
    
    // Test sending prebuilt message
    messages.send(empty);
    CPPUNIT_ASSERT(system.messageCount() == 2);
    
    // Test sending unregistered prebuild message
    messages.send(dummy);
    CPPUNIT_ASSERT(system.messageCount() == 2);
    
}
