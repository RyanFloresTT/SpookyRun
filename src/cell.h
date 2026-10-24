#pragma once
#include "raylib.h"
#include "config.h"

// Maybe player can configure this to help them out
constexpr auto RedAttack = Color{255, 0, 0, 65};

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

inline void DrawCell(const CellState state, const int x, const int y) {
    const int px = x * TileSize;
    const int py = y * TileSize;

    switch (state) {
        case CellState::Empty: DrawRectangle(px, py, TileSize, TileSize, GetBoardColor(x, y)); break;
        case CellState::Attack: DrawRectangle(px, py, TileSize, TileSize, RedAttack); break;
        case CellState::Occupied: break;
    }
}