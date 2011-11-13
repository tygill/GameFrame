cmake_minimum_required(VERSION 2.8)

# Directory:
# GameFrame/test


# Test/example game

include_directories(${GameFrame_SOURCE_DIR}/test)
#link_directories (${GameFrame_BINARY_DIR})


# Include CppUnit
find_package(CppUnit REQUIRED)
if (NOT CppUnit_FOUND)
    message(FATAL_ERROR "CppUnit was not found")
endif (NOT CppUnit_FOUND)
include_directories("${CppUnit_INCLUDE_DIR}")

set(GameFrame_TEST_CXX
    "main.cpp"
    "PositionComponent.cpp"
    "VelocityComponent.cpp"
    "TestSystem.cpp"
    #"DummyComponent.cpp"
    #"DummyMessage.cpp"
    #"EmptyMessage.cpp"
    "TestEntityTemplate.cpp"
    "EntityManagerTest.cpp"
    "MessageManagerTest.cpp"
)

file(GLOB_RECURSE GameFrame_TEST_H "*.h")

add_executable(test ${GameFrame_TEST_CXX} ${GameFrame_TEST_H})
target_link_libraries(test GameFrame ${Boost_LIBRARIES})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(test ${CppUnit_DEBUG_LIBRARIES})
else (CMAKE_BUILD_TYPE STREQUAL "Debug")
    #message(FATAL_ERROR "Not building release versions! -${CMAKE_BUILD_TYPE} -${CppUnit_DEBUG_LIBRARIES} -${CppUnit_LIBRARIES}")
    target_link_libraries(test ${CppUnit_LIBRARIES})
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

if (UNIX)
    add_custom_command(TARGET test POST_BUILD COMMAND ${EXECUTABLE_OUTPUT_PATH}/test)
elseif (WIN32)
    add_custom_command(TARGET test POST_BUILD COMMAND "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/test.exe")
endif (UNIX)

