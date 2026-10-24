#include "lost_scene.h"
#include "scene_manager.h"
#include "level_menu.h"
#include "opening_scene.h"
#include "../config.h"
#include "../ui/button.h"

void LostScene::Draw() {
    background.Draw();

    constexpr float center_x = TotalBoardWidth / 2.0f;
    UI::CenteredText(center_x, 120, "You Lost!", 64, DARKGRAY);

    if (UI::CenteredButton(center_x, 260, "Level Menu")) SceneManager::Get().GoTo<LevelMenu>();
    if (UI::CenteredButton(center_x, 336, "Main Menu"))  SceneManager::Get().GoTo<OpeningScene>();
    if (UI::CenteredButton(center_x, 412, "Quit"))       SceneManager::Get().Quit();
}