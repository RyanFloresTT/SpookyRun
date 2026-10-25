#pragma once
#include "piece.h"

class Board;

class Rook : public Piece {
public:
    Rook(Board& grid, const int x, const int y, const std::vector<Vector2>& patrol_sequence) : Piece(
        grid, x, y, PieceType::Rook, patrol_sequence) {}

    void SetHitSquares() override;
};
