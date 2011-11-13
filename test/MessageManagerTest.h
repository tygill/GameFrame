#pragma once
#ifndef idF5B85067_F040_4D36_9642248A2D59B17F
#define idF5B85067_F040_4D36_9642248A2D59B17F

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <gf/MessageManager.h>
#include "TestSystem.h"

class MessageManagerTest : public CppUnit::TestFixture {
public:
    void setUp();
    void tearDown();
    
    CPPUNIT_TEST_SUITE(MessageManagerTest);

    CPPUNIT_TEST(messageTypeGeneration);
    CPPUNIT_TEST(sendMessage);
    
    CPPUNIT_TEST_SUITE_END();
    
    void messageTypeGeneration();
    void sendMessage();

private:
    gf::MessageManager messages;
    TestSystem system;

};

#endif // header
