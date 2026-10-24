#pragma once
#include "piece.h"

class Board;

class Queen : public Piece {
public:
    Queen(Board& grid, int x, int y) : Piece(grid, x, y, PieceType::Queen) {}

    void SetHitSquares() override;
};