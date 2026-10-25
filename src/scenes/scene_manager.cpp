//
// Created by rryan on 10/23/2026.
//

#include "scene_manager.h"

#include "level_menu.h"
#include "raylib.h"
#include "opening_scene.h"
#include "../levels/level_scene.h"

void SceneManager::display_cursor() {
    const auto [x, y] = GetMousePosition();
    DrawTexture(AssetManager::GetCursor(), static_cast<int>(x - 15), static_cast<int>(y - 10), WHITE);
}

void SceneManager::Run() {
    while (!WindowShouldClose() && running) {
        AssetManager::UpdateMusic();

        if (pending) {
            current = pending();
            pending = nullptr;
            current->Enter();
        }
        if (!current) break;

        current->Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(RAYWHITE);
        current->Draw();
        display_cursor();
        EndDrawing();
    }
}