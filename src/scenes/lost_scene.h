#pragma once
#include "level_menu.h"
#include "raylib.h"
#include "scene.h"
#include "../config.h"

class LostScene : public Scene {
public:
    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            SceneManager::Get().GoTo<LevelMenu>();
        }
    }
    void Draw() override {
        DrawText("You Lost!", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
    }
};
