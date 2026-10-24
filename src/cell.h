#pragma once
#include "raylib.h"
#include "config.h"
#include "raii/assets.h"

// Maybe player can configure this to help them out
constexpr auto RedAttack = Color{255, 0, 0, 65};

enum class CellState {
    Empty,
    Pawn,
    Rook,
    Attack
};

struct CellInfo {
    CellState state;
    int x, y;
};

// todo: fix these static casts :)))))
inline void DrawAsset(const Asset asset, const int px, const int py) {
    const Texture2D& tex = AssetManager::GetTexture(asset);
    const Rectangle  source{0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height)};
    const Rectangle  dest{static_cast<float>(px), static_cast<float>(py), static_cast<float>(TileSize), static_cast<float>(TileSize)};
    DrawTexturePro(tex, source, dest, Vector2{0, 0}, 0.0f, WHITE);
}

inline Color GetBoardColor(const int x, const int y) {
    return (x + y) % 2 == 0 ? Color{121, 72, 57, 255} : Color{93, 50, 49, 255};
}

inline void DrawCell(const CellState state, const int x, const int y) {
    const int px = x * TileSize;
    const int py = y * TileSize;

    switch (state) {
        case CellState::Empty: DrawRectangle(px, py, TileSize, TileSize, GetBoardColor(x, y)); break;
        case CellState::Pawn:  DrawAsset(Asset::Pawn, px, py);  break;
        case CellState::Rook:  DrawAsset(Asset::Rook, px, py);  break;
        case CellState::Attack: DrawRectangle(px, py, TileSize, TileSize, RedAttack); break;
    }
}