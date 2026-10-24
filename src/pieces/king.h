#pragma once
#include "piece.h"

class Board;

class King : public Piece {
public:
    King(Board& grid, int x, int y) : Piece(grid, x, y, PieceType::King) {}

    void SetHitSquares() override;
};