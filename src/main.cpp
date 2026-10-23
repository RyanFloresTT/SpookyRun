#include <memory>

#include "config.h"
#include "grid.h"
#include "raylib.h"

int main() {
    const auto BackgroundGrid = std::make_shared<Grid>(CellState::Empty);
    auto PlayableGrid = std::make_shared<Grid>(CellState::Empty);

    InitWindow(TotalBoardWidth, TotalBoardWidth, "Pawn Run");
    SetTargetFPS(60);

    bool started = false;
    bool playerInitialized = false;

    while (!WindowShouldClose()) {
        if (!started && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) started = true;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (!started) {
            DrawText("Click to start", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
        } else {
            //BackgroundGrid->Draw();
            PlayableGrid->Draw();

            if (IsKeyPressed(KEY_ONE)) {
                PlayableGrid->Set(3, 3, CellState::Pawn);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlayableGrid->SetPlayer(GetMouseX() / TileSize, GetMouseY() / TileSize);
            }

            if (!playerInitialized) {
                playerInitialized = true;
                PlayableGrid->SetPlayer(BoardSize/2, BoardSize - 1);
            }
        }



        EndDrawing();
    }

    CloseWindow();
    return 0;
}
