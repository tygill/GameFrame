cmake_minimum_required(VERSION 2.8)

# Directory:
# GameFrame/gf/sdl


# Standard SDL Library (libGameFrameSDL.a, GameFrameSDL.dll

set(GameFrame_SDL_LIB_CXX
    "GameFrameSDL.cpp"
    "PositionComponent.cpp"
    "RenderableComponent.cpp"
    "SDLEventSystem.cpp"
    "WindowSystem.cpp"
    "Sprite.cpp"
    "ImageTemplate.cpp"
)

file(GLOB GameFrame_SDL_LIB_H "*.h")

# Global linkage libraries

set(GameFrameSDL_EXTRA_LIBS
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    CACHE
    FILEPATH
    "Full path to all GameFrameSDL dependent libraries"
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
add_library(GameFrameSDL ${GameFrame_SDL_LIB_CXX} ${GameFrame_SDL_LIB_H})
set(GameFrameSDL_LIBS
    ${GameFrameSDL}
    ${GameFrameSDL_EXTRA_LIBS}
    CACHE
    FILPATH
    "Full path to all GameFrameSDL libraries."
)
endif(CMAKE_BUILD_TYPE STREQUAL Release)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
add_library(GameFrameSDLd ${GameFrame_SDL_LIB_CXX} ${GameFrame_SDL_LIB_H})
set(GameFrameSDLd_LIBS
    ${GameFrameSDLd}
    ${GameFrameSDL_EXTRA_LIBS}
    CACHE
    FILPATH
    "Full path to all GameFrameSDL debug libraries."
)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

#find_library(GameFrameSDL_LIBRARY GameFrameSDL ${LIBRARY_OUTPUT_PATH})


