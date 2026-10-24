#pragma once
#include <vector>

#include "../scenes/scene.h"
#include "../cell.h"
#include <memory>
#include "../board.h"
#include "../pieces/piece.h"

class Level : public Scene {
public:
    explicit Level(const int level) {this->level = level;}

    void Enter() override {
        playable.AddPiece(PieceType::Pawn,   0, 7);   // player

        playable.AddPiece(PieceType::Rook,   1, 5);   // RA
        playable.AddPiece(PieceType::Rook,   2, 3);   // RC
        playable.AddPiece(PieceType::Knight, 1, 2);   // F
        playable.AddPiece(PieceType::Knight, 3, 2);   // N
        playable.AddPiece(PieceType::Rook,   7, 2);   // G
        playable.AddPiece(PieceType::Knight, 0, 1);   // Z
    }
    void Update(const float dt) override {
        playable.Update(dt);
    }

    void Draw() override {
        background.Draw();
        playable.Draw();
    }

private:
    Board background{CellState::Empty};
    Board playable{CellState::Empty};
    std::vector<std::unique_ptr<Piece>> pieces;
    int level;
};
