#pragma once
#include "piece.h"

class Board;

class Knight : public Piece {
public:
    Knight(Board& grid, const int x, const int y, const std::vector<Vector2>& patrol_sequence) : Piece(grid, x, y, PieceType::Knight, patrol_sequence) {}

    void SetHitSquares() override;
};