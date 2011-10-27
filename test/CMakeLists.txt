cmake_minimum_required(VERSION 2.8)
#project(GAMEFRAME)

# Directory:
# GameFrame/test


# Test/example game

include_directories(${GAMEFRAME_SOURCE_DIR})
include_directories(${GAMEFRAME_SOURCE_DIR}/test)
#link_directories (${GAMEFRAME_BINARY_DIR})


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system chrono thread)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost was not found")
endif (NOT Boost_FOUND)

find_package(CppUnit REQUIRED)
if (NOT CppUnit_FOUND)
    message(FATAL_ERROR "CppUnit was not found")
endif (NOT CppUnit_FOUND)

set(GAMEFRAME_TEST_CXX
    "main.cpp"
    "PositionComponent.cpp"
    "VelocityComponent.cpp"
    "EntityManagerTest.cpp"
)

add_executable(test ${GAMEFRAME_TEST_CXX})
target_link_libraries(test GameFrame ${Boost_LIBRARIES} ${CppUnit_LIBRARIES})

add_custom_command(TARGET test POST_BUILD COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test)

