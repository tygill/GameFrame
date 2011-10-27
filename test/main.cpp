#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

// This sub project performs unit tests on all of the classes that make up the main GameFrame module
/*
Test Outline:
 GameFrame
  Running
   Single thread
    No systems
    One system
    Multiple systems
   Multi thread
    One/One
    One/Multi
    Multi/One
    Multi/Multi
   Non-default thread
    Multi systems on non-default thread
 EntityManager
  Classes that must be tested: Entity, EntityComponent, EntityTemplate, EntityManager
  Basic EntityComponent implementations
   PositionComponent
   VelocityComponent
   HealthComponent
  Basic EntityTemplate implementations
   BulletTemplate
   EnemyTemplate
   BlockTemplate
*/

// Include all headers that register tests here
#include "EntityManagerTest.h"

int main(int argc, char* argv[]) {
    
    std::cout << "Starting Tests" << std::endl;
    
    // Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    // Run the tests.
    bool wasSucessful = runner.run();

    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}
