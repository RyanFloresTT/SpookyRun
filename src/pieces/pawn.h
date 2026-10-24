#pragma once
#include "piece.h"

class Board;

class Pawn : public Piece{
public:
    Pawn(const int startX, const int startY, Board& PlayableGrid)
    : Piece(PlayableGrid, startX, startY, PieceType::Pawn) {}

    void SetHitSquares() override;
    bool validate_pawn_move(int target_x, int target_y, int dx, int dy, CellState destination_state) const;

    void Move(int target_x, int target_y);
    void Update(float dt) override;
    void Init() const;
    bool PlayerWon() const;
};
