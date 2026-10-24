#pragma once
#include "piece.h"

class Board;

class Knight : public Piece {
public:
    Knight(Board& grid, const int x, const int y) : Piece(grid, x, y, PieceType::Knight) {}

    void SetHitSquares() override;
};