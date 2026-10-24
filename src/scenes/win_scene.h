#pragma once
#include "raylib.h"
#include "scene.h"
#include "../config.h"

class WinScene : public Scene {
public:
    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            SceneManager::Get().GoTo(SceneType::Level);
        }
    }
    void Draw() override {
        DrawText("You Won!", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
    }
};
