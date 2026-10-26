#include "lost_scene.h"
#include "scene_manager.h"
#include "level_menu.h"
#include "opening_scene.h"
#include "../config.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"

void LostScene::Draw() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BEIGE);
    constexpr float center_x = TotalBoardWidth / 2.0f;
    UI::CenteredText(center_x, 240, "You Lost!", 96, BLACK);

    Rectangle r{center_x - 120, 450, 240, 56};
    if (UI::Button(r,"Try Again", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().GoTo<Level>(retry_level);

    r.y += 200;
    if (UI::Button(r,"Level Menu", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().GoTo<LevelMenu>();

    r.y += 65;
    if (UI::Button(r,"Main Menu", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().GoTo<OpeningScene>();

    r.y += 65;
    if (UI::Button(r,"Quit", 24, AssetManager::Get(TextureAssets::MenuButton))) SceneManager::Get().Quit();
}
