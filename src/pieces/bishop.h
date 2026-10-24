#pragma once
#include "piece.h"

class Board;

class Bishop : public Piece {
public:
    Bishop(Board& grid, int x, int y) : Piece(grid, x, y, PieceType::Bishop) {}

    void SetHitSquares() override;
};