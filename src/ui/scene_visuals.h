#pragma once
#include <cmath>
#include "button.h"
#include "../assets.h"
#include "lantern/raii/asset_scope.h"

namespace SceneVisuals {
    inline void Sprite(const Texture2D& texture, const float center_x, const float y,
                       const float      size, const Color tint = WHITE) {
        const Rectangle source{0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
        const Rectangle dest{center_x - size / 2, y, size, size};
        DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0, tint);
    }

    inline void Backdrop(AssetScope& assets, const Color accent) {
        const float width  = static_cast<float>(GetScreenWidth());
        const float height = static_cast<float>(GetScreenHeight());
        const float tile   = width / 12;
        ClearBackground(Color{24, 28, 27, 255});

        const Texture2D& floor = assets.Get<Texture2D>(Assets::Images::WhiteFloors::FLOOR2);
        for (int row = 0; row * tile < height; ++row) {
            for (int column = 0; column < 12; ++column) {
                const bool alternate = (row + column) % 2 == 0;
                Sprite(floor, (column + 0.5f) * tile, row * tile, tile,
                       alternate ? Color{42, 49, 46, 255} : Color{36, 42, 40, 255});
            }
        }

        const Texture2D& top_wall    = assets.Get<Texture2D>(Assets::Images::TOP_WALL);
        const Texture2D& bottom_wall = assets.Get<Texture2D>(Assets::Images::BOTTOM_WALL);
        const Texture2D& left_wall   = assets.Get<Texture2D>(Assets::Images::LEFT_WALL);
        const Texture2D& right_wall  = assets.Get<Texture2D>(Assets::Images::RIGHT_WALL);

        for (int column = 1; column < 11; ++column) {
            Sprite(top_wall, (column + 0.5f) * tile, 0, tile, GRAY);
            Sprite(bottom_wall, (column + 0.5f) * tile, height - tile, tile, GRAY);
        }
        for (int row = 0; row * tile < height; ++row) {
            Sprite(left_wall, tile / 2, row * tile, tile, GRAY);
            Sprite(right_wall, width - tile / 2, row * tile, tile, GRAY);
        }
        Sprite(assets.Get<Texture2D>(Assets::Images::CORNER_BL), tile / 2, height - tile, tile, GRAY);
        Sprite(assets.Get<Texture2D>(Assets::Images::CORNER_BR), width - tile / 2, height - tile, tile, GRAY);

        DrawRectangle(static_cast<int>(width * 0.24f), static_cast<int>(height * 0.105f),
                      static_cast<int>(width * 0.52f), 3, accent);
        DrawRectangle(static_cast<int>(width * 0.24f), static_cast<int>(height * 0.87f),
                      static_cast<int>(width * 0.52f), 3, accent);
    }

    inline void Heading(AssetScope& assets, const char* text, const Color color) {
        const float center_x = GetScreenWidth() / 2.0f;
        const float y        = GetScreenHeight() * 0.16f;
        const Font& font     = assets.Get<Font>(Assets::Font::SUPPLY_CENTER_REGULAR);
        UI::CenteredText(font, center_x + 3, y + 5, text, 72, Color{12, 15, 14, 255});
        UI::CenteredText(font, center_x, y, text, 72, color);
    }

    inline float Bob() {
        return static_cast<float>(std::sin(GetTime() * 2.5)) * 5;
    }
}
