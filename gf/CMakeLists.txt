cmake_minimum_required(VERSION 2.8)

# Directory:
# GameFrame/gf


# Core library (libGameFrame.a, GameFrame.dll, etc.)

# Move to gf folder - build the binary there.

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++0x")

set(GameFrame_LIB_CXX
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
    
    "core/CoreSystem.cpp"
    "core/CoreMessages.cpp"
)

file(GLOB GameFrame_LIB_H "*.h")
file(GLOB GameFrame_CORE_LIB_H "core/*.h")

# Global linkage libraries

if (UNIX)
set(GameFrame_EXTRA_LIBS
    ${Boost_LIBRARIES}
    "rt"
    CACHE
    FILEPATH
    "Full paths to all dependent libraries for GameFrame"
)
elseif (WIN32)
set(GameFrame_EXTRA_LIBS
    ${Boost_LIBRARIES}
    CACHE
    FILEPATH
    "Full paths to all dependent libraries for GameFrame"
)
endif (UNIX)

if(CMAKE_BUILD_TYPE STREQUAL Release)
add_library(GameFrame ${GameFrame_LIB_CXX} ${GameFrame_LIB_H} ${GameFrame_CORE_LIB_H})
set(GameFrame_LIBS
    ${GameFrame}
    ${GameFrame_EXTRA_LIBS}
    CACHE
    FILEPATH
    "Full path to all GameFrame libraries."
)
endif(CMAKE_BUILD_TYPE STREQUAL Release)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
add_library(GameFramed ${GameFrame_LIB_CXX} ${GameFrame_LIB_H} ${GameFrame_CORE_LIB_H})
set(GameFramed_LIBS
    ${GameFramed}
    ${GameFrame_EXTRA_LIBS}
    CACHE
    FILEPATH
    "Full path to all GameFrame debug libraries."
)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

#find_library(GameFrame_LIBRARY GameFrame ${LIBRARY_OUTPUT_PATH})

# Add the core component libraries
add_subdirectory(core)
add_subdirectory(sdl)
