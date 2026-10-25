#pragma once
#include "piece.h"

class Board;

class King : public Piece {
public:
    King(Board& grid, const int x, const int y, const std::vector<Vector2>& patrol_sequence) : Piece(
        grid, x, y, PieceType::King, patrol_sequence) {}

    void SetHitSquares() override;
};
