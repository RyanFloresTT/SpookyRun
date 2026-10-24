#pragma once

#include "piece_type.h"
#include "../cell.h"
#include "../raii/assets.h"

class Board;

class Piece {
public:
    Piece(Board& Grid, int x, int y, PieceType type) : PlayableGrid(Grid), info{CellState::Occupied, x, y} {
        this->type = type;
    };
    virtual      ~Piece() = default;
    virtual void SetHitSquares() = 0;
    void         Draw() {
        DrawAsset(type, info.x * TileSize, info.y * TileSize);
    }

    // todo: fix these static casts :)))))
    static void DrawAsset(const PieceType asset, const int px, const int py) {
        const Texture2D& tex = AssetManager::GetTexture(asset);
        const Rectangle  source{0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height)};
        const Rectangle  dest{static_cast<float>(px), static_cast<float>(py), static_cast<float>(TileSize), static_cast<float>(TileSize)};
        DrawTexturePro(tex, source, dest, Vector2{0, 0}, 0.0f, WHITE);
    }

    virtual void Update(float dt) = 0;

    CellInfo GetCellInfo() const { return info; };

protected:
    Board& PlayableGrid;
    CellInfo info;
    PieceType type;
};
