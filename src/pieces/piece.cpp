//
// Created by rryan on 10/24/2026.
//
// src/pieces/piece.cpp
#include "piece.h"
#include "../board.h"

void Piece::Draw() const {
    float progress = is_moving ? animation_timer / move_duration : 1.0f;
    progress = 1.0f - (1.0f - progress) * (1.0f - progress) * (1.0f - progress);

    const float tile_size = game_board.GetTileSize();
    const float px = (from_x + (info.x - from_x) * progress) * tile_size;
    const float py = (from_y + (info.y - from_y) * progress) * tile_size;
    DrawAsset(type, px, py, tile_size);
}

void Piece::DetectPlayer() {
    if (type == PieceType::Pawn) return;

    for (const auto [x, y] : hit_squares) {
        if (game_board.PieceTypeAt(PieceType::Pawn, x, y)) {
            MoveTo(x, y);
            return;
        }
    }
}

void Piece::OnMovementFinished() {
    PlaySound(AssetManager::GetSound());
    if (type == PieceType::Pawn) return;
    has_hit_player = true;
}
