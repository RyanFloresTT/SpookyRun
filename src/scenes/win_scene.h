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
    explicit WinScene(AssetStore& asset_store) : Scene(asset_store) {
        SceneVisuals::Preload(assets);
        assets.LoadAll<Texture2D>({Assets::Images::STAR, Skins::Selected, Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE});
        assets.Load<Font>(Assets::Font::SUPPLY_CENTER_REGULAR);
        assets.Load<Sound>(Assets::SFX::BUTTON_CLICK);
    }

    void Update(float) override {}

    void Draw() override {
        constexpr Color accent{238, 206, 104, 255};
        const float center_x = GetScreenWidth() / 2.0f;
        const float height = static_cast<float>(GetScreenHeight());
        SceneVisuals::Backdrop(assets, accent);
        SceneVisuals::Heading(assets, "You Won!", accent);

        SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::STAR), center_x, height * 0.30f + SceneVisuals::Bob(), 96);
        SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::STAR), center_x - 112, height * 0.35f - SceneVisuals::Bob(), 48);
        SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::STAR), center_x + 112, height * 0.35f - SceneVisuals::Bob(), 48);
        SceneVisuals::Sprite(assets.Get<Texture2D>(Skins::Selected), center_x, height * 0.42f, 88);

        const Font&      font       = assets.Get<Font>(Assets::Font::SUPPLY_CENTER_REGULAR);
        const Sound&     click      = assets.Get<Sound>(Assets::SFX::BUTTON_CLICK);
        const Texture2D& background = assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE);

        Rectangle r{center_x - 120, height * 0.57f, 240, 56};
        if (UI::Button(font, click, r,"Level Menu", 24, background)) scene_manager->GoTo<LevelMenu>();

        r.y += height * 0.10f;
        if (UI::Button(font, click, r,"Main Menu", 24, background)) scene_manager->GoTo<OpeningScene>();

        r.y += height * 0.10f;
        if (UI::Button(font, click, r,"Quit", 24, background)) scene_manager->Quit();

    }
};
