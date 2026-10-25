#pragma once

#include "../scenes/scene.h"
#include "../cell.h"

#include "level_manager.h"
#include "../board.h"
#include "../scenes/lost_scene.h"

class Level : public Scene {
public:
    explicit Level(const int level) { this->level = level; }

    void Enter() override {
        LevelManager::LoadLevel(level, playable);
    }

    void Update(const float dt) override {
        playable.Update(dt);

        if (playable.PlayerCaptured()) {
            SceneManager::Get().GoTo<LostScene>(level);
        }

        if (IsKeyPressed(KEY_R)) {
            SceneManager::Get().GoTo<Level>(level);
        }
    }

    void Draw() override {
        playable.Draw();
    }

private:
    Board playable{CellState::Empty};
    int   level;
};
