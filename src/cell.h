#pragma once
#include "raylib.h"

// Maybe player can configure this to help them out
constexpr auto RedAttack = Color{255, 0, 0, 12};

enum class CellState {
    Empty,
    Occupied,
    Attack,
    Border
};

struct CellInfo {
    CellState state;
    int       x, y;
};

class Cell {
public:
    static void DrawBGCell(const Texture2D& tex, const float px, const float py, const float tile_size, const float rotation = 0.f) {
        const Rectangle source{0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height)};
        const Rectangle dest{px, py, tile_size, tile_size};
        DrawTexturePro(tex, source, dest, Vector2{0, 0}, rotation, WHITE);
    }

    static void DrawCell(const CellState state, const int x, const int y, const float tile_size) {
        Rectangle bounds{x * tile_size, y * tile_size, tile_size, tile_size};

        const std::string_view floor_asset_path = x == 1 && y == 1 ? Assets::Images::FLOOR_CORNER :
                                         x == 1 || y == 1 ? Assets::Images::FLOOR_EDGE :
                                         Assets::Images::WhiteFloors::FLOOR2;

        const float rotation = x == 1 ? -90.f : 0.f;

        if (rotation != 0.f) {
            bounds.y += tile_size;
        }

        DrawBGCell(assets.Get<Texture2D>(floor_asset_path), bounds.x, bounds.y, tile_size, rotation);

        if (state == CellState::Attack) {
            DrawRectangleRec(bounds, RedAttack);
        }
    }

    static void DrawBorderCell(const int x, const int y, const float tile_size, const int board_size) {
        const bool top = y == 0;
        const bool bottom = y == board_size - 1;
        const bool left = x == 0;
        const bool right = x == board_size - 1;
        if (!top && !bottom && !left && !right) return;

        const std::string_view wall_path = bottom && left ? Assets::Images::CORNER_BL :
                                   bottom && right ? Assets::Images::CORNER_BR :
                                   left ? Assets::Images::LEFT_WALL :
                                   right ? Assets::Images::RIGHT_WALL :
                                   top ? Assets::Images::TOP_WALL : Assets::Images::BOTTOM_WALL;

        DrawBGCell(assets.Get<Texture2D>(wall_path), x * tile_size, y * tile_size, tile_size);
    }
private:
    static AssetStore assets;
};
