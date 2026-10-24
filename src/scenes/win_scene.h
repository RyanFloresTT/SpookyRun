#pragma once
#include "raylib.h"
#include "scene.h"
#include "scene_manager.h"
#include "../config.h"
#include "../ui/button.h"
#include "level_menu.h"
#include "opening_scene.h"

class WinScene : public Scene {
public:
    void Update(float) override {}

    void Draw() override {
        background.Draw();

        constexpr float center_x = TotalBoardWidth / 2.0f;

        UI::CenteredText(center_x, 120, "You Won!", 64, DARKGRAY);

        if (UI::CenteredButton(center_x, 260, "Level Menu")) SceneManager::Get().GoTo<LevelMenu>();
        if (UI::CenteredButton(center_x, 336, "Main Menu"))  SceneManager::Get().GoTo<OpeningScene>();
        if (UI::CenteredButton(center_x, 412, "Quit"))       SceneManager::Get().Quit();
    }

private:
    Board background{CellState::Empty};
};