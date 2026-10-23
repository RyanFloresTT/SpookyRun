#include <memory>

#include "config.h"
#include "grid.h"
#include "raylib.h"

int main() {
    const auto BackgroundGrid = std::make_shared<Grid<CellState>>(BoardSize, BoardSize, CellState::Empty);
    auto PlayableGrid = std::make_shared<Grid<CellState>>(BoardSize, BoardSize, CellState::Empty);

    InitWindow(TotalBoardWidth, TotalBoardWidth, "Pawn Run");
    SetTargetFPS(60);

    bool started = false;

    while (!WindowShouldClose()) {
        if (!started && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) started = true;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (!started) {
            DrawText("Click to start", TotalBoardWidth/2 - 64, TotalBoardWidth/2, 48, DARKGRAY);
        } else {
            BackgroundGrid->Draw();
            PlayableGrid->Draw();
        }

        if (IsKeyPressed(KEY_ONE)) {
            PlayableGrid->SetCell(3, 3, CellState::Pawn);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
