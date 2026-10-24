#pragma once
#include "raylib.h"
#include "scene.h"
#include "../config.h"
#include "scene_manager.h"
#include "../board.h"
#include "../raii/assets.h"
#include "../scenes/level_menu.h"

class OpeningScene : public Scene {
public:
    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            SceneManager::Get().GoTo<LevelMenu>();
        }
    }
    void Draw() override {
        background.Draw();

        const Font& font = AssetManager::GetFont();
        constexpr float size = 48.0f;
        constexpr float spacing = 2.0f;

        const auto text   = "Click to start!";
        const auto  [x, y] = MeasureTextEx(font, text, size, spacing);

        DrawTextEx(font, text,
                   Vector2{ TotalBoardWidth / 2.0f - x / 2.0f,
                            TotalBoardWidth / 2.0f - y / 2.0f },
                   size, spacing, WHITE);

    }

private:
    Board background{CellState::Empty};
};
