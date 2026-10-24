#pragma once
#include "level_menu.h"
#include "raylib.h"
#include "scene.h"
#include "scene_manager.h"
#include "../config.h"

class WinScene : public Scene {
public:
    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            SceneManager::Get().GoTo<LevelMenu>();
        }
    }
    void Draw() override {
        DrawText("You Won!", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
    }
};
