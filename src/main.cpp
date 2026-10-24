#include "config.h"
#include "raii/window.h"
#include "scenes/scene_manager.h"

int main() {
    Window window(TotalBoardWidth, "Pawn Run", 60);

    SceneManager::Get().GoTo(SceneType::Opening);
    SceneManager::Get().Run();
}
