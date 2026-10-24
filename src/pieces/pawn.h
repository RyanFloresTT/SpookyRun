#pragma once
#include "piece.h"

class Board;

class Pawn : public Piece{
public:
    Pawn(const int startX, const int startY, Board& PlayableGrid)
    : Piece(PlayableGrid, startX, startY, PieceType::Pawn) {}

    void SetHitSquares() override;

    void Move(int dx, int dy);
    void Update(float dt) override;
    void Init() const;
    bool PlayerWon() const;
};
