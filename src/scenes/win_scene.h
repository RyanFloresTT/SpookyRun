#pragma once
#include "raylib.h"
#include "scene.h"
#include "scene_manager.h"
#include "../config.h"
#include "../ui/button.h"
#include "level_menu.h"
#include "opening_scene.h"
#include "../ui/scene_visuals.h"

class WinScene : public Scene {
public:
    void Update(float) override {}

    void Draw() override {
        constexpr Color accent{238, 206, 104, 255};
        const float center_x = GetScreenWidth() / 2.0f;
        const float height = static_cast<float>(GetScreenHeight());
        SceneVisuals::Backdrop(accent);
        SceneVisuals::Heading("You Won!", accent);

        SceneVisuals::Sprite(TextureAssets::Star, center_x, height * 0.30f + SceneVisuals::Bob(), 96);
        SceneVisuals::Sprite(TextureAssets::Star, center_x - 112, height * 0.35f - SceneVisuals::Bob(), 48);
        SceneVisuals::Sprite(TextureAssets::Star, center_x + 112, height * 0.35f - SceneVisuals::Bob(), 48);
        SceneVisuals::Sprite(TextureAssets::Player, center_x, height * 0.42f, 88);

        Rectangle r{center_x - 120, height * 0.57f, 240, 56};
        if (UI::Button(r,"Level Menu", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().GoTo<LevelMenu>();

        r.y += height * 0.10f;
        if (UI::Button(r,"Main Menu", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().GoTo<OpeningScene>();

        r.y += height * 0.10f;
        if (UI::Button(r,"Quit", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().Quit();

    }
};
