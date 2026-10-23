#include <memory>

#include "config.h"
#include "grid.h"
#include "raylib.h"
#include "player.h"

int main() {
    const auto BackgroundGrid = std::make_shared<Grid>(CellState::Empty);
    auto PlayableGrid = std::make_shared<Grid>(CellState::Empty);
    auto PlayerPawn = std::make_shared<Player>(BoardSize/2, BoardSize - 1, *PlayableGrid);

    InitWindow(TotalBoardWidth, TotalBoardWidth, "Pawn Run");
    SetTargetFPS(60);

    bool started = false;
    bool playerInitialized = false;
    float rookTimer = 0.f;

    while (!WindowShouldClose()) {
        if (!started && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) started = true;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (!started) {
            DrawText("Click to start", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
        } else {
            BackgroundGrid->Draw();
            PlayableGrid->Draw();

            if (IsKeyPressed(KEY_ONE)) {
                PlayableGrid->Set(3, 3, CellState::Pawn);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlayerPawn->Move(GetMouseX() / TileSize, GetMouseY() / TileSize);
            }

            if (!playerInitialized) {
                playerInitialized = true;
                PlayerPawn->Init();
            }
        }

        if (rookTimer > 5.f) {
            PlayableGrid->Set(3, 3, CellState::Rook);
        } else {
            rookTimer += GetFrameTime();
        }

        if (PlayerPawn->PlayerWon()) {
            DrawText("Click to start", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
