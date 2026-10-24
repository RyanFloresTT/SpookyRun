//
// Created by rryan on 10/23/2026.
//

#include "scene_manager.h"
#include "raylib.h"
#include "opening_scene.h"
#include "level_scene.h"
#include "lost_scene.h"
#include "win_scene.h"

void SceneManager::Run() {
    while (!WindowShouldClose()) {
        if (pending) {
            // TODO: maybe I can do a transition here if I have some time :)
            Apply(*pending);
            pending.reset();
        }
        if (!current) break;

        current->Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(RAYWHITE);
        current->Draw();
        EndDrawing();
    }
}

void SceneManager::Apply(const SceneType type) {
    switch (type) {
        case SceneType::Opening: current = std::make_unique<OpeningScene>(); break;
        case SceneType::Level:   current = std::make_unique<LevelScene>();   break;
        case SceneType::Win:     current = std::make_unique<WinScene>();     break;
        case SceneType::Lose:     current = std::make_unique<LostScene>();     break;
    }
    current->Enter();
}