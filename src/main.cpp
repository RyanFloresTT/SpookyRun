#include "assets.h"
#include "lantern/assets/asset_store.h"
#include "lantern/raii/asset_scope.h"
#include "lantern/game/game.h"
#include "scenes/opening_scene.h"

int main() {
    auto game = Game(920, 920, "Spooky Run", 60);
    AssetStore global_store;
    AssetScope scope(global_store);

    scope.Load<Music>(Assets::Music::NASTELBOM_SPOKY_HALLOWEEN_617000);
    scope.Load<Texture2D>(Assets::Cursor::HAND_SMALL_POINT);

    const Music& music = scope.Get<Music>(Assets::Music::NASTELBOM_SPOKY_HALLOWEEN_617000);

    PlayMusicStream(music);
    SetMusicVolume(music, 0.1f);
    HideCursor();

    game.GetSceneManager().SetFrameCallback([&] {
        UpdateMusicStream(music);
        const auto [x, y] = GetMousePosition();
        DrawTexture(scope.Get<Texture2D>(Assets::Cursor::HAND_SMALL_POINT), static_cast<int>(x - 15), static_cast<int>(y - 10), WHITE);
    });

    game.GetSceneManager().GoTo<OpeningScene>();
    game.Run();
}
