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
        src/board.h
        src/config.h
        src/cell.h
        src/pieces/pawn.cpp
        src/pieces/pawn.h
        src/scenes/scene.h
        src/scenes/opening_scene.h
        src/scenes/level_scene.h
        src/scenes/scene_manager.h
        src/raii/window.h
        src/raii/assets.h
        src/scenes/win_scene.h
        src/scenes/scene_manager.cpp
        src/scenes/lost_scene.h
        src/pieces/rook.cpp
        src/pieces/piece.h
        src/pieces/piece_factory.cpp
        src/pieces/piece_factory.h
        src/pieces/rook.h
        src/pieces/piece_type.h
        src/pieces/bishop.cpp
        src/pieces/bishop.h
        src/pieces/knight.cpp
        src/pieces/knight.h
        src/pieces/king.cpp
        src/pieces/king.h
        src/pieces/queen.cpp
        src/pieces/queen.h
        src/scenes/level_menu.h
)
target_link_libraries(solojam PRIVATE raylib)

if (EMSCRIPTEN)
    set_target_properties(solojam PROPERTIES SUFFIX ".html")
    target_link_options(solojam PRIVATE
            -sUSE_GLFW=3
            -sASYNCIFY
            -sALLOW_MEMORY_GROWTH=1
            "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/assets@/assets"
    )
else()
    add_custom_command(TARGET solojam POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:solojam>/assets)
endif()