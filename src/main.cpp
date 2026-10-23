#include "config.h"
#include "raii/window.h"
#include "scenes/scene_manager.h"
#include "scenes/opening_scene.h"
#include "scenes/level_scene.h"

int main() {
    Window window(TotalBoardWidth, "Pawn Run", 60);

    SceneManager game;

    game.Add<OpeningScene>()
        .Add<LevelScene>();

    game.Run();
}