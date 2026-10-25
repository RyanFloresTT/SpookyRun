#pragma once
#include <vector>

#include "../scenes/scene.h"
#include "../cell.h"
#include <memory>

#include "level_manager.h"
#include "../board.h"
#include "../pieces/piece.h"
#include "../scenes/lost_scene.h"

class Level : public Scene {
public:
    explicit Level(const int level) {this->level = level;}

    void Enter() override {
        LevelManager::LoadLevel(level, playable);
    }
    void Update(const float dt) override {
        playable.Update(dt);

        if (playable.PlayerCaptured()) {
            SceneManager::Get().GoTo<LostScene>();
        }
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
