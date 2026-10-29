#include "lantern/game/game.h"
#include "scenes/opening_scene.h"

int main() {
    auto game = Game(920, 920, "Spooky Run", 60);
    AssetManager::load_assets();

    game.GetSceneManager().GoTo<OpeningScene>();
    game.Run();

    AssetManager::unload_assets();
}
