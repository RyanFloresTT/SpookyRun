#include "config.h"
#include "raii/window.h"
#include "scenes/opening_scene.h"
#include "scenes/scene_manager.h"

int main() {
    Window window(TotalBoardWidth, "Pawn Run", 60);

    SceneManager::Get().GoTo<OpeningScene>();
    SceneManager::Get().Run();
}
