#include "lantern/game/game.h"
#include "scenes/opening_scene.h"

int main() {
    auto game = Game(920, 920, "Spooky Run", 60);
    AssetManager::load_assets();

    const Music& music = AssetManager::Get(MusicAssets::Seaside);

    PlayMusicStream(music);
    SetMusicVolume(music, 0.1f);
    HideCursor();

    game.GetSceneManager().SetFrameCallback([] {
        UpdateMusicStream(AssetManager::Get(MusicAssets::Seaside));
        const auto [x, y] = GetMousePosition();
        DrawTexture(AssetManager::Get(TextureAssets::Cursor), static_cast<int>(x - 15), static_cast<int>(y - 10), WHITE);
    });

    game.GetSceneManager().GoTo<OpeningScene>();
    game.Run();

    AssetManager::unload_assets();
}
