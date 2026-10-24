//
// Created by rryan on 10/24/2026.
//
// src/pieces/piece.cpp
#include "piece.h"
#include "../board.h"

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
