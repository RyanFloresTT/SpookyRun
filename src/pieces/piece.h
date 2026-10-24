#pragma once

#include "piece_type.h"
#include "../cell.h"
#include "../raii/assets.h"

class Board;

class Piece {
public:
    Piece(Board& Grid, int x, int y, PieceType type)
        : game_board(Grid), info{CellState::Occupied, x, y}, type(type), from_x(x), from_y(y) {}

    virtual ~Piece() = default;
    virtual void SetHitSquares() = 0;

    // Logical position changes instantly, the visual catches up over move_duration.
    void MoveTo(int new_x, int new_y) {
        from_x = info.x;
        from_y = info.y;
        info.x = new_x;
        info.y = new_y;
        animation_timer = 0.0f;
        is_moving = true;
    }

    virtual void Update(float dt) {
        if (!is_moving) return;
        animation_timer += dt;
        if (animation_timer >= move_duration) {
            animation_timer = move_duration;
            is_moving = false;
        }
    }

    void Draw() const {
        float t = is_moving ? animation_timer / move_duration : 1.0f;
        t = 1.0f - (1.0f - t) * (1.0f - t) * (1.0f - t); // ease-out cubic

        const float px = (from_x + (info.x - from_x) * t) * TileSize;
        const float py = (from_y + (info.y - from_y) * t) * TileSize;
        DrawAsset(type, px, py);
    }

    static void DrawAsset(const PieceType asset, const float px, const float py) {
        const Texture2D& tex = AssetManager::GetTexture(asset);
        const Rectangle source{0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height)};
        const Rectangle dest{px, py, static_cast<float>(TileSize), static_cast<float>(TileSize)};
        DrawTexturePro(tex, source, dest, Vector2{0, 0}, 0.0f, WHITE);
    }

    bool     IsAnimating() const { return is_moving; }
    CellInfo GetCellInfo() const { return info; }

protected:
    Board&    game_board;
    CellInfo  info;
    PieceType type;

    int   from_x = 0, from_y = 0;
    bool  is_moving = false;
    float animation_timer = 0.0f;
    float move_duration = 0.15f; // seconds
};
