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
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BEIGE);
        constexpr float center_x = TotalBoardWidth / 2.0f;

        UI::CenteredText(center_x, 240, "You Won!", 96, DARKGRAY);

        Rectangle r{center_x - 120, 500, 240, 56};
        if (UI::Button(r,"Level Menu", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().GoTo<LevelMenu>();

        r.y += 100;
        if (UI::Button(r,"Main Menu", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().GoTo<OpeningScene>();

        r.y += 100;
        if (UI::Button(r,"Quit", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().Quit();

    }
};
