#pragma once
#include "piece.h"

class Board;

class Knight : public Piece {
public:
    Knight(Board& grid, int x, int y) : Piece(grid, x, y, PieceType::Knight) {}

    void SetHitSquares() override;
};