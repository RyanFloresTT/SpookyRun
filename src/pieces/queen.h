#pragma once
#include "piece.h"

class Board;

class Queen : public Piece {
public:
    Queen(Board& grid, const int x, const int y) : Piece(grid, x, y, PieceType::Queen) {}

    void SetHitSquares() override;
    void DetectPlayer() override;
};