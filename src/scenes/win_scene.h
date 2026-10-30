#pragma once
#include "raylib.h"
#include "../ui/button.h"
#include "level_menu.h"
#include "opening_scene.h"
#include "../assets.h"
#include "../skins.h"
#include "../ui/scene_visuals.h"
#include "lantern/scene/scene.h"
#include "lantern/scene/scene_manager.h"

class WinScene : public Scene {
public:
    explicit WinScene(AssetStore& asset_store) : Scene(asset_store) {}

    void Update(float) override {}

    void Draw() override {
        constexpr Color accent{238, 206, 104, 255};
        const float center_x = GetScreenWidth() / 2.0f;
        const float height = static_cast<float>(GetScreenHeight());
        SceneVisuals::Backdrop(assets, accent);
        SceneVisuals::Heading(assets, "You Won!", accent);

        SceneVisuals::Sprite(*assets.Get<Texture2D>(Assets::Images::STAR), center_x, height * 0.30f + SceneVisuals::Bob(), 96);
        SceneVisuals::Sprite(*assets.Get<Texture2D>(Assets::Images::STAR), center_x - 112, height * 0.35f - SceneVisuals::Bob(), 48);
        SceneVisuals::Sprite(*assets.Get<Texture2D>(Assets::Images::STAR), center_x + 112, height * 0.35f - SceneVisuals::Bob(), 48);
        SceneVisuals::Sprite(*assets.Get<Texture2D>(Skins::Selected), center_x, height * 0.42f, 88);

        Rectangle r{center_x - 120, height * 0.57f, 240, 56};
        if (UI::Button(assets, r,"Level Menu", 24, *assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE))) scene_manager->GoTo<LevelMenu>();

        r.y += height * 0.10f;
        if (UI::Button(assets, r,"Main Menu", 24, *assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE))) scene_manager->GoTo<OpeningScene>();

        r.y += height * 0.10f;
        if (UI::Button(assets, r,"Quit", 24, *assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE))) scene_manager->Quit();

    }
};
