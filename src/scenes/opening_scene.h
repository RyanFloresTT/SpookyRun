#pragma once
#include "raylib.h"
#include "../board.h"
#include "../scenes/level_menu.h"
#include "../ui/button.h"
#include "../skins.h"
#include "../ui/scene_visuals.h"

#include "lantern/scene/scene.h"
#include "lantern/scene/scene_manager.h"

class OpeningScene : public Scene {
public:
    explicit OpeningScene(AssetStore& asset_store) : Scene(asset_store) {
        const std::vector textures_to_load = {
            Assets::Images::WhiteFloors::FLOOR2, Assets::Images::ROOK, Assets::Images::BISHOP, Assets::Images::STAR, Skins::Selected,
        };

        const std::vector fonts_to_load = {Assets::Font::SUPPLY_CENTER_REGULAR};

        assets.LoadAll<Texture2D>(textures_to_load);
        assets.LoadAll<Font>(fonts_to_load);
    }

    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scene_manager->GoTo<LevelMenu>();
        }
    }

    void Draw() override {
        constexpr Color accent{164, 205, 173, 255};
        const float center_x = GetScreenWidth() / 2.0f;
        const float height = static_cast<float>(GetScreenHeight());
        SceneVisuals::Backdrop(assets, accent);
        SceneVisuals::Heading(assets, "Spooky Run", accent);

        const float tile = GetScreenWidth() / 9.0f;
        for (int column = -2; column <= 2; ++column) {
            SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::WhiteFloors::FLOOR2), center_x + column * tile,
                                 height * 0.43f, tile, Color{132, 145, 132, 255});
        }
        SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::ROOK), center_x - tile * 2, height * 0.43f - 28, tile);
        SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::BISHOP), center_x + tile * 2, height * 0.43f - 28, tile);
        SceneVisuals::Sprite(assets.Get<Texture2D>(Skins::Selected), center_x, height * 0.39f + SceneVisuals::Bob(), tile * 1.3f);
        SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::STAR), center_x, height * 0.31f, 40);

        const float pulse = 0.8f + static_cast<float>(std::sin(GetTime() * 3)) * 0.2f;
        UI::CenteredText(assets.Get<Font>(Assets::Font::SUPPLY_CENTER_REGULAR), center_x, height * 0.7f, "Click to start!", 36, Fade(WHITE, pulse));
    }
};
