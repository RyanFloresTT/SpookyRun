#pragma once
#include "raylib.h"
#include "scene.h"
#include "../config.h"
#include "../cell.h"
#include "../player.h"
#include "../grid.h"

class LevelScene : public Scene {
public:
    void Enter() override {
        player.Init();
        ROOK_TXT = LoadTextureFromImage( LoadImage("assets/rook.png"));
    }

    void Update(float dt) override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            player.Move(GetMouseX() / TileSize, GetMouseY() / TileSize);

        rookTimer += dt;
        if (rookTimer > 1.f) playable.Set(4, 4, CellState::Rook);

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
