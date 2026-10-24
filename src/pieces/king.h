#pragma once
#include "piece.h"

class Board;

class King : public Piece {
public:
    King(Board& grid, const int x, const int y) : Piece(grid, x, y, PieceType::King) {}

    void SetHitSquares() override;
};