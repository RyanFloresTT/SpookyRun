#pragma once
#include "piece.h"

class Board;

class Rook : public Piece {
public:

    Rook(Board& grid, int x, int y) : Piece(grid, x, y, PieceType::Rook) {}

    void SetHitSquares() override;
};