cmake_minimum_required(VERSION 3.20)
project(solojam CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUEz
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
        lantern
        GIT_REPOSITORY https://github.com/RyanFloresTT/lantern.git
        GIT_TAG shared-ptr-assets
)
FetchContent_MakeAvailable(lantern)

add_executable(solojam
        src/main.cpp
        src/board.h
        src/config.h
        src/cell.h
        src/pieces/pawn.cpp
        src/pieces/pawn.h
        src/scenes/opening_scene.h
        src/levels/level_scene.h
        src/scenes/win_scene.h
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
        src/ui/button.h
        src/pieces/piece.cpp
        src/scenes/lost_scene.cpp
        src/scenes/level_menu.cpp
        src/levels/level_manager.h
        src/save/save_manager.h
        src/save/desktop_save_manager.cpp
        src/save/web_save_manager.cpp
        src/save/web_save_manager.h
        src/save/desktop_save_manager.h
        src/assets.h
        src/skins.h
        src/ui/menu_grid.h
        src/scenes/skin_menu.h
        src/scenes/skin_menu.cpp
)
target_link_libraries(solojam PRIVATE raylib nlohmann_json::nlohmann_json lantern)

if (EMSCRIPTEN)
    set_target_properties(solojam PROPERTIES SUFFIX ".html")
    target_link_options(solojam PRIVATE
            -sUSE_GLFW=3
            -sASYNCIFY
            -sALLOW_MEMORY_GROWTH=1
            -sEXPORTED_RUNTIME_METHODS=HEAPF32,HEAP32,HEAPU8
            "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/assets@/assets"
    )
else ()
    add_custom_command(TARGET solojam POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:solojam>/assets)
endif ()