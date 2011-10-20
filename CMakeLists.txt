cmake_minimum_required(VERSION 2.8)
project(GAMEFRAME)


# Core library (libGameFrame.a, GameFrame.dll, etc.)

# Move to gf folder - build the binary there.
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++0x")

set(GAMEFRAME_CORE_LIB_CXX
    "gf/Entity.cpp"
    "gf/EntityComponent.cpp"
    "gf/EntityManager.cpp"
    "gf/EntitySystem.cpp"
    "gf/EntitySystemThread.cpp"
    "gf/EntityTemplate.cpp"
    "gf/GameFrame.cpp"
    "gf/Message.cpp"
    "gf/MessageManager.cpp"
    "gf/Resource.cpp"
    "gf/ResourceManager.cpp"
    "gf/ResourceTemplate.cpp"
)

add_library(GameFrame ${GAMEFRAME_CORE_LIB_CXX})

add_subdirectory(test)



# include_directories("${SOME_VAR_NAME}/directory")
#link_directories("${PROJECT_BINARY_DIR}") #CMAKE_CURRENT_BINARY_DIR

#file(GLOB webclient_cpp
#    "*.cpp"
#    "*.h"
#)

#set(webserver_cpp
#    "flo.cpp"
#)

#find_package(Boost REQUIRED COMPONENTS thread)
#if (NOT Boost_FOUND)
#    message(FATAL_ERROR "Boost was not found")
#endif (NOT Boost_FOUND)

#add_executable(flo ${webserver_cpp})
#target_link_libraries(flo ${Boost_LIBRARIES})

#file(COPY "${PROJECT_SOURCE_DIR}/www" DESTINATION "${PROJECT_BINARY_DIR}")

#add_subdirectory (Hello) 
#add_library (Hello hello.cxx)

# install (TARGETS download DESTINATION bin)
