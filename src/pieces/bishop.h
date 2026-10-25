#pragma once
#include "piece.h"

class Board;

class Bishop : public Piece {
public:
    Bishop(Board& grid, const int x, const int y, const std::vector<Vector2>& patrol_sequence) : Piece(
        grid, x, y, PieceType::Bishop, patrol_sequence) {}

    void SetHitSquares() override;
};