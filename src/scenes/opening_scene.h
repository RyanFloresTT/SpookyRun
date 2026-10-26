#pragma once
#include "raylib.h"
#include "scene.h"
#include "../config.h"
#include "scene_manager.h"
#include "../board.h"
#include "../scenes/level_menu.h"
#include "../ui/button.h"

class OpeningScene : public Scene {
public:
    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            SceneManager::Get().GoTo<LevelMenu>();
        }
    }

    void Draw() override {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BEIGE);

        UI::CenteredText(TotalBoardWidth / 2.0f, TotalBoardWidth / 2.0f - 500 / 2.0f, "Spooky Run", 96, BLACK);
        UI::CenteredText(TotalBoardWidth / 2.0f, TotalBoardWidth / 2.0f + 100 / 2.0f, "Click to start!", 48, WHITE);
    }
};
