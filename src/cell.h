#pragma once
#include "raylib.h"
#include "config.h"
#include "raii/assets.h"

// Maybe player can configure this to help them out
constexpr auto RedAttack = Color{255, 0, 0, 0};

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

inline void DrawBGCell(const Texture2D& tex, const float px, const float py, const float tile_size, const float rotation = 0.f) {
    const Rectangle source{0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height)};
    const Rectangle dest{px, py, tile_size, tile_size};
    DrawTexturePro(tex, source, dest, Vector2{0, 0}, rotation, WHITE);
}

inline void DrawCell(const CellState state, const int x, const int y, const float tile_size) {
    Rectangle bounds{x * tile_size, y * tile_size, tile_size, tile_size};

    const TextureAssets floor_asset = x == 1 && y == 1 ? TextureAssets::FloorCorner :
                                     x == 1 || y == 1 ? TextureAssets::FloorEdge :
                                     TextureAssets::WhiteFloor2;

    const float rotation = x == 1 ? -90.f : 0.f;

    if (rotation != 0.f) {
        bounds.y += tile_size;
    }

    DrawBGCell(AssetManager::Get(floor_asset), bounds.x, bounds.y, tile_size, rotation);

    if (state == CellState::Attack) {
        DrawRectangleRec(bounds, RedAttack);
    }
}

inline void DrawBorderCell(const int x, const int y, const float tile_size, const int board_size) {
    const bool top = y == 0;
    const bool bottom = y == board_size - 1;
    const bool left = x == 0;
    const bool right = x == board_size - 1;
    if (!top && !bottom && !left && !right) return;

    const TextureAssets wall = bottom && left ? TextureAssets::BottomLeftCorner :
                               bottom && right ? TextureAssets::BottomRightCorner :
                               left ? TextureAssets::LeftWall :
                               right ? TextureAssets::RightWall :
                               top ? TextureAssets::TopWall : TextureAssets::BottomWall;

    DrawBGCell(AssetManager::Get(wall), x * tile_size, y * tile_size, tile_size);
}
