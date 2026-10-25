#pragma once
#include "raylib.h"
#include "config.h"

// Maybe player can configure this to help them out
constexpr auto RedAttack = Color{255, 0, 0, 0};

enum class CellState {
    Empty,
    Occupied,
    Attack
};

struct CellInfo {
    CellState state;
    int x, y;
};

inline Color GetBoardColor(const int x, const int y) {
    return (x + y) % 2 == 0 ? Color{121, 72, 57, 255} : Color{93, 50, 49, 255};
}

inline void DrawCell(const CellState state, const int x, const int y, const float tile_size) {
    const Rectangle bounds{x * tile_size, y * tile_size, tile_size, tile_size};
    DrawRectangleRec(bounds, GetBoardColor(x, y));
    if (state == CellState::Attack) {
        DrawRectangleRec(bounds, RedAttack);
    }
}