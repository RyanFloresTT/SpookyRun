#pragma once
#include "piece.h"

class Board;

class Queen : public Piece {
public:
    Queen(Board& grid, const int x, const int y, const std::vector<Vector2>& patrol_sequence) : Piece(grid, x, y, PieceType::Queen, patrol_sequence) {}

    void SetHitSquares() override;
};