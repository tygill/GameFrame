cmake_minimum_required(VERSION 2.8)

# Directory:
# GameFrame/gf


# Core library (libGameFrame.a, GameFrame.dll, etc.)

# Move to gf folder - build the binary there.

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++0x")

set(GameFrame_CORE_LIB_CXX
    "Entity.cpp"
    "EntityComponent.cpp"
    "EntityManager.cpp"
    "EntitySystem.cpp"
    "EntitySystemThread.cpp"
    "EntityTemplate.cpp"
    "Exceptions.cpp"
    "GameFrame.cpp"
    "Global.cpp"
    "Message.cpp"
    "MessageManager.cpp"
    "Resource.cpp"
    "ResourceManager.cpp"
    "ResourceTemplate.cpp"
)

file(GLOB_RECURSE GameFrame_CORE_LIB_H "*.h")

add_library(GameFrame ${GameFrame_CORE_LIB_CXX} ${GameFrame_CORE_LIB_H})

