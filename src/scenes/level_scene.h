#pragma once
#include <vector>

#include "scene.h"
#include "../config.h"
#include "../cell.h"
#include <memory>
#include "../board.h"
#include "../pieces/piece.h"
#include "../pieces/piece_factory.h"

class LevelScene : public Scene {
public:
    void Enter() override {
        playable.AddPiece(PieceType::Pawn, 3, BoardSize - 1);
        playable.AddPiece(PieceType::Rook, 2, BoardSize - 3);
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
};
