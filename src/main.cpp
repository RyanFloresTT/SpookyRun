#include "grid.h"
#include "raylib.h"

int main() {
    Grid grid;

    InitWindow(grid.BoardSize, grid.BoardSize, "Pawn Run");
    SetTargetFPS(60);

    bool started = false;

    while (!WindowShouldClose()) {
        if (!started && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) started = true;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (!started) {
            DrawText("Click to start", 310, 215, 24, DARKGRAY);
        } else {
            grid.Draw();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
