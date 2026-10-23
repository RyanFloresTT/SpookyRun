cmake_minimum_required(VERSION 3.20)
project(solojam CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(solojam
        src/main.cpp
        src/grid.h
        src/config.h
        src/cell.h
        src/player.cpp
        src/player.h
        src/scenes/scene.h
        src/scenes/opening_scene.h
        src/scenes/level_scene.h
        src/scenes/scene_manager.h
        src/raii/window.h
        src/raii/assets.h
)
target_link_libraries(solojam PRIVATE raylib)

if (EMSCRIPTEN)
    set_target_properties(solojam PROPERTIES SUFFIX ".html")
    target_link_options(solojam PRIVATE
            -sUSE_GLFW=3
            -sASYNCIFY
            -sFORCE_FILESYSTEM=1
            "-sTOTAL_MEMORY=67108864"
    )
endif()
