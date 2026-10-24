#pragma once
#include "piece.h"

class Board;

class Bishop : public Piece {
public:
    Bishop(Board& grid, const int x, const int y) : Piece(grid, x, y, PieceType::Bishop) {}

    void SetHitSquares() override;
    void DetectPlayer() override;
};