#pragma once
#include <cmath>
#include "button.h"

namespace SceneVisuals {
    inline void Sprite(const TextureAssets asset, const float center_x, const float y,
                       const float size, const Color tint = WHITE) {
        const Texture2D& texture = AssetManager::Get(asset);
        const Rectangle source{0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
        const Rectangle dest{center_x - size / 2, y, size, size};
        DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0, tint);
    }

    inline void Backdrop(const Color accent) {
        const float width = static_cast<float>(GetScreenWidth());
        const float height = static_cast<float>(GetScreenHeight());
        const float tile = width / 12;
        ClearBackground(Color{24, 28, 27, 255});

        for (int row = 0; row * tile < height; ++row) {
            for (int column = 0; column < 12; ++column) {
                const bool alternate = (row + column) % 2 == 0;
                Sprite(TextureAssets::WhiteFloor2, (column + 0.5f) * tile, row * tile, tile,
                       alternate ? Color{42, 49, 46, 255} : Color{36, 42, 40, 255});
            }
        }

        for (int column = 1; column < 11; ++column) {
            Sprite(TextureAssets::TopWall, (column + 0.5f) * tile, 0, tile, GRAY);
            Sprite(TextureAssets::BottomWall, (column + 0.5f) * tile, height - tile, tile, GRAY);
        }
        for (int row = 0; row * tile < height; ++row) {
            Sprite(TextureAssets::LeftWall, tile / 2, row * tile, tile, GRAY);
            Sprite(TextureAssets::RightWall, width - tile / 2, row * tile, tile, GRAY);
        }
        Sprite(TextureAssets::BottomLeftCorner, tile / 2, height - tile, tile, GRAY);
        Sprite(TextureAssets::BottomRightCorner, width - tile / 2, height - tile, tile, GRAY);

        DrawRectangle(static_cast<int>(width * 0.24f), static_cast<int>(height * 0.105f),
                      static_cast<int>(width * 0.52f), 3, accent);
        DrawRectangle(static_cast<int>(width * 0.24f), static_cast<int>(height * 0.87f),
                      static_cast<int>(width * 0.52f), 3, accent);
    }

    inline void Heading(const char* text, const Color color) {
        const float center_x = GetScreenWidth() / 2.0f;
        const float y = GetScreenHeight() * 0.16f;
        UI::CenteredText(center_x + 3, y + 5, text, 72, Color{12, 15, 14, 255});
        UI::CenteredText(center_x, y, text, 72, color);
    }

    inline float Bob() {
        return static_cast<float>(std::sin(GetTime() * 2.5)) * 5;
    }
}