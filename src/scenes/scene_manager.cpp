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

        /*
         * Things needed for transitions
         *  1. Current scene loaded
         *  2. Play "animation", doesn't have to be a scene, just drawing an object
         *  3. Swap current to pending by the time animation ends
         *
         *  I'll start by loading something between, maybe giving a delay between loads too
         *
         *  Might need a flag that triggers when to load next scene, this is all in one if statement
         */

        if (transitioning&& transition_progress<transition_duration) {
            transition_progress += GetFrameTime();
        }
        else {
            transitioning       = false;
            transition_progress = 0;
        }

        if (pending && (!transitioning || transition_progress >= swap_time)) {
            current = pending();
            pending = nullptr;
            current->Enter();
        }
        if (!current) break;

        current->Update(GetFrameTime());

        BeginDrawing();

        ClearBackground(RAYWHITE);
        current->Draw();

        if (transitioning) {
            const float t     = transition_progress / transition_duration; // 0 -> 1
            const float alpha = 1.0f - std::abs(t * 2.0f - 1.0f);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
        }

        display_cursor();
        EndDrawing();
    }
}