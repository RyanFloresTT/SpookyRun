// scene_manager.h
#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "raylib.h"
#include "scene.h"

class SceneManager {
public:
    template <typename T, typename... Args>
    SceneManager& Add(Args&&... args) {
        scenes.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *this;
    }

    void Run() {
        if (scenes.empty()) return;
        scenes[current]->Enter();

        while (!WindowShouldClose()) {
            Scene& scene = *scenes[current];
            scene.Update(GetFrameTime());

            BeginDrawing();
            ClearBackground(RAYWHITE);
            scene.Draw();
            EndDrawing();

            if (scene.Done() && !Advance()) break;
        }
    }

private:
    bool Advance() {
        if (current + 1 >= scenes.size()) return false;
        scenes[++current]->Enter();
        return true;
    }

    std::vector<std::unique_ptr<Scene>> scenes;
    size_t current = 0;
};