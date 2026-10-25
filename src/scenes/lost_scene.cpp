#include "lost_scene.h"
#include "scene_manager.h"
#include "level_menu.h"
#include "opening_scene.h"
#include "../config.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"

void LostScene::Draw() {
    background.Draw();

    constexpr float center_x = TotalBoardWidth / 2.0f;
    UI::CenteredText(center_x, 100, "You Lost!", 72, BLACK);

    if (UI::CenteredButton(center_x, 450, "Try Again"))  SceneManager::Get().GoTo<Level>(retry_level);

    if (UI::CenteredButton(center_x, 660, "Level Menu")) SceneManager::Get().GoTo<LevelMenu>();
    if (UI::CenteredButton(center_x, 736, "Main Menu"))  SceneManager::Get().GoTo<OpeningScene>();
    if (UI::CenteredButton(center_x, 812, "Quit"))       SceneManager::Get().Quit();
}