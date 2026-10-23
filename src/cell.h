#pragma once
#include "raylib.h"
#include "config.h"

enum class CellState {
    Empty,
    Pawn,
    Rook
};

inline Color GetBoardColor(const int x, const int y) {
    return (x + y) % 2 == 0 ? WHITE : BLACK;
}

inline void DrawCell(const CellState state, const int x, const int y) {
    const int px = x * TileSize;
    const int py = y * TileSize;

    switch (state) {
        case CellState::Empty: DrawRectangle(px, py, TileSize, TileSize, GetBoardColor(x, y)); break;
        case CellState::Pawn:  DrawRectangle(px, py, TileSize, TileSize, PINK); break;
        case CellState::Rook:  DrawRectangle(px, py, TileSize, TileSize, RED);  break;
    }
}