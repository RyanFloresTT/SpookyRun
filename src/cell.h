#pragma once
#include "raylib.h"
#include "config.h"
#include "raii/assets.h"

// Maybe player can configure this to help them out
constexpr auto RedAttack = Color{255, 0, 0, 0};

enum class CellState {
    Empty,
    Occupied,
    Attack
};

struct CellInfo {
    CellState state;
    int       x, y;
};

inline void DrawBGCell(const Texture2D& tex, const float px, const float py, const float tile_size) {
    const Rectangle source{0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height)};
    const Rectangle dest{px, py, tile_size, tile_size};
    DrawTexturePro(tex, source, dest, Vector2{0, 0}, 0.0f, WHITE);
}

inline void DrawCell(const CellState state, const int x, const int y, const float tile_size) {
    const Rectangle bounds{x * tile_size, y * tile_size, tile_size, tile_size};
    DrawBGCell(AssetManager::GetFloor(x, y), bounds.x, bounds.y, tile_size);
    if (state == CellState::Attack) {
        DrawRectangleRec(bounds, RedAttack);
    }
}