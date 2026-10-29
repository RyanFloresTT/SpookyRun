#pragma once
#include "raylib.h"
#include "../board.h"
#include "../scenes/level_menu.h"
#include "../ui/button.h"
#include "../ui/scene_visuals.h"

#include "lantern/scene/scene.h"
#include "lantern/scene/scene_manager.h"

class OpeningScene : public Scene {
public:
    void Update(float) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scene_manager->GoTo<LevelMenu>();
        }
    }

    void Draw() override {
        constexpr Color accent{164, 205, 173, 255};
        const float center_x = GetScreenWidth() / 2.0f;
        const float height = static_cast<float>(GetScreenHeight());
        SceneVisuals::Backdrop(accent);
        SceneVisuals::Heading("Spooky Run", accent);

        const float tile = GetScreenWidth() / 9.0f;
        for (int column = -2; column <= 2; ++column) {
            SceneVisuals::Sprite(TextureAssets::WhiteFloor2, center_x + column * tile,
                                 height * 0.43f, tile, Color{132, 145, 132, 255});
        }
        SceneVisuals::Sprite(TextureAssets::Rook, center_x - tile * 2, height * 0.43f - 28, tile);
        SceneVisuals::Sprite(TextureAssets::Bishop, center_x + tile * 2, height * 0.43f - 28, tile);
        SceneVisuals::Sprite(TextureAssets::Player, center_x, height * 0.39f + SceneVisuals::Bob(), tile * 1.3f);
        SceneVisuals::Sprite(TextureAssets::Star, center_x, height * 0.31f, 40);

        const float pulse = 0.8f + static_cast<float>(std::sin(GetTime() * 3)) * 0.2f;
        UI::CenteredText(center_x, height * 0.7f, "Click to start!", 36, Fade(WHITE, pulse));
    }
};
