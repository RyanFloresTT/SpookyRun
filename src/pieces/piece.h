#pragma once

#include <cmath>
#include <vector>

#include "piece_type.h"
#include "../cell.h"
#include "../raii/assets.h"

class Board;

class Piece {
public:
    Piece(Board& Grid, const int x, const int y, const PieceType type)
        : type(type), game_board(Grid), info{CellState::Occupied, x, y}, from_x(x), from_y(y) {}

    virtual ~Piece() = default;
    virtual void SetHitSquares() = 0;

    void DetectPlayer();

    void MoveTo(const int new_x, const int new_y) {
        from_x = info.x;
        from_y = info.y;
        info.x = new_x;
        info.y = new_y;

        const auto dx = static_cast<float>(new_x - from_x);
        const auto dy = static_cast<float>(new_y - from_y);
        const float distance = std::sqrt(dx * dx + dy * dy);   // in tiles

        move_duration   = distance * seconds_per_tile;
        animation_timer = 0.0f;
        is_moving       = true;
    }

    void OnMovementFinished();

    bool handle_movement_animation(const float dt) {
        if (!is_moving) return true;
        animation_timer += dt;
        if (animation_timer >= move_duration) {
            animation_timer = move_duration;
            is_moving       = false;
            OnMovementFinished();
        }
        return false;
    }

    virtual void Update(const float dt) {
        if (has_hit_player) return;

        if (is_moving) {
            handle_movement_animation(dt);
            return;
        }
        DetectPlayer();
    }

    void Draw() const;

    static void DrawAsset(const PieceType asset, const float px, const float py, const float tile_size) {
        const Texture2D& tex = AssetManager::GetTexture(asset);
        const Rectangle source{0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height)};
        const Rectangle dest{px, py, tile_size, tile_size};
        DrawTexturePro(tex, source, dest, Vector2{0, 0}, 0.0f, WHITE);
    }


    bool      IsAnimating() const { return is_moving; }
    CellInfo  GetCellInfo() const { return info; }
    bool      HasHitPlayer() const { return has_hit_player; }
    PieceType type;

protected:
    Board&    game_board;
    CellInfo  info;

    int   from_x = 0, from_y = 0;
    bool  is_moving = false;
    float animation_timer = 0.0f;
    float move_duration = 0.15f; // seconds
    float seconds_per_tile = 0.15f;

    std::vector<Vector2> hit_squares;

private:
    bool has_hit_player = false;
};
