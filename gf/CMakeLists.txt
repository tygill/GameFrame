cmake_minimum_required(VERSION 2.8)
#project(GAMEFRAME)

# Directory:
# GameFrame/test


# Core library (libGameFrame.a, GameFrame.dll, etc.)

# Move to gf folder - build the binary there.
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++0x")

set(GAMEFRAME_CORE_LIB_CXX
    "Entity.cpp"
    "EntityComponent.cpp"
    "EntityManager.cpp"
    "EntitySystem.cpp"
    "EntitySystemThread.cpp"
    "EntityTemplate.cpp"
    "Exceptions.cpp"
    "GameFrame.cpp"
    "Message.cpp"
    "MessageManager.cpp"
    "Resource.cpp"
    "ResourceManager.cpp"
    "ResourceTemplate.cpp"
)

add_library(GameFrame ${GAMEFRAME_CORE_LIB_CXX})

