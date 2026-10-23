#pragma once
#include "raylib.h"
#include "scene.h"
#include "../config.h"
#include "../cell.h"
#include "../player.h"
#include "../grid.h"

class LevelScene : public Scene {
public:
    void Enter() override { player.Init(); }

    void Update(float dt) override {
        if (IsKeyPressed(KEY_ONE)) playable.Set(3, 3, CellState::Pawn);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            player.Move(GetMouseX() / TileSize, GetMouseY() / TileSize);

        rookTimer += dt;
        if (rookTimer > 5.f) playable.Set(3, 3, CellState::Rook);

        if (player.PlayerWon()) done = true;
    }

    void Draw() const override {
        background.Draw();
        playable.Draw();
    }

private:
    Grid background{CellState::Empty};
    Grid playable{CellState::Empty};
    Player player{BoardSize / 2, BoardSize - 1, playable};
    float rookTimer = 0.f;
};
