#cmake_minimum_required(VERSION 2.8)
#project(GAMEFRAME)


# Test/example game

include_directories(${GAMEFRAME_SOURCE_DIR})
link_directories (${GAMEFRAME_BINARY_DIR})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++0x")

find_package(Boost REQUIRED COMPONENTS system chrono thread)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost was not found")
endif (NOT Boost_FOUND)

set(GAMEFRAME_TEST_CXX
    "main.cpp"
)

add_executable(test ${GAMEFRAME_TEST_CXX})
target_link_libraries(test GameFrame ${Boost_LIBRARIES})

