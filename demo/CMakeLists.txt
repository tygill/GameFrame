cmake_minimum_required(VERSION 2.8)

# Directory:
# GameFrame/demo


# Demo/example game

include_directories(${GameFrame_SOURCE_DIR}/demo)
#link_directories (${GameFrame_BINARY_DIR})


set(GameFrame_DEMO_CXX
    "main.cpp"
)

file(GLOB GameFrame_DEMO_H "*.h")

add_executable(demo ${GameFrame_DEMO_CXX} ${GameFrame_DEMO_H})
#target_link_libraries(demo ${GameFrame_LIBS} ${Boost_LIBRARIES} GameFrameSDL ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(demo GameFramed GameFrameSDLd)
else (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(demo GameFrame GameFrameSDL)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

target_link_libraries(demo
    #debug GameFramed
    #general GameFrame
    ${GameFrame_EXTRA_LIBS}
    #debug GameFrameSDLd
    #general GameFrameSDL
    ${GameFrameSDL_EXTRA_LIBS})

if (UNIX)
    #add_custom_command(TARGET test POST_BUILD COMMAND ${EXECUTABLE_OUTPUT_PATH}/test)
elseif (WIN32)
    #add_custom_command(TARGET test POST_BUILD COMMAND "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/test.exe")
    
    # Copy the dlls for the SDL_Image and SDL libraries
    # This is a very computer specific hack, though usually these paths should
    # be right on Windows
    string(REGEX REPLACE "/" "\\\\" WIN_STYLE_EXE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})
    
    string(STRIP ${SDL_INCLUDE_DIR} SDL_DYN_DIR)
    string(REGEX REPLACE "/" "\\\\" SDL_DYN_DIR ${SDL_DYN_DIR})
    add_custom_command(TARGET demo POST_BUILD COMMAND copy "${SDL_DYN_DIR}\\..\\lib\\*.dll" "${WIN_STYLE_EXE_OUTPUT_PATH}\\${CMAKE_BUILD_TYPE}")
    
    string(STRIP ${SDLIMAGE_INCLUDE_DIR} SDLIMAGE_DYN_DIR)
    string(REGEX REPLACE "/" "\\\\" SDLIMAGE_DYN_DIR ${SDLIMAGE_DYN_DIR})
    add_custom_command(TARGET demo POST_BUILD COMMAND copy "${SDLIMAGE_DYN_DIR}\\..\\lib\\*.dll" "${WIN_STYLE_EXE_OUTPUT_PATH}\\${CMAKE_BUILD_TYPE}")
endif (UNIX)

