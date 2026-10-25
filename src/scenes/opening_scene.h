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


        const auto title_text   = "Spooky Run";
        const auto  [tx, ty] = MeasureTextEx(font, title_text, 72, spacing);

        const auto click_text   = "Click to start!";
        const auto  [cx, cy] = MeasureTextEx(font, click_text, size, spacing);

        DrawTextEx(font, title_text,
                   Vector2{ TotalBoardWidth / 2.0f - tx / 2.0f,
                            TotalBoardWidth / 3.0f - ty / 2.0f },
                   72, spacing, WHITE);

        DrawTextEx(font, click_text,
           Vector2{ TotalBoardWidth / 2.0f - cx / 2.0f,
                    TotalBoardWidth / 2.0f - cy / 2.0f },
           size, spacing, WHITE);

    }

private:
    Board background{CellState::Empty};
};
