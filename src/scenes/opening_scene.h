#pragma once
#include "raylib.h"
#include "scene.h"
#include "../config.h"

class OpeningScene : public Scene {
public:
    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) done = true;
    }
    void Draw() const override {
        DrawText("Click to start", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
    }
};
