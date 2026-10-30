#include "level_menu.h"
#include "skin_menu.h"
#include "lantern/scene/scene_manager.h"
#include "../levels/level_scene.h"
#include "../skins.h"
#include "../ui/button.h"
#include "../ui/menu_grid.h"
#include "../ui/scene_visuals.h"

void LevelMenu::Enter() {
    level_count    = LevelManager::GetLevelCount();
    unlocked_count = LevelManager::LoadProgress();
    first_row      = 0;
}

void LevelMenu::Update(float) {
    MenuGrid::Scroll(first_row, level_count);
}

void LevelMenu::draw_level_buttons() {
    const Texture2D& background = assets.Get<Texture2D>(Assets::UI::BUTTON_BG);
    const Texture2D& star       = assets.Get<Texture2D>(Assets::Images::STAR);

    // Levels are 1-based; grid indices are 0-based.
    for (int i = MenuGrid::FirstIndex(first_row); i < MenuGrid::EndIndex(first_row, level_count); ++i) {
        const int         level  = i + 1;
        const Rectangle   bounds = MenuGrid::Bounds(i, first_row);
        const std::string label  = std::to_string(level);

        if (level == unlocked_count) MenuGrid::Highlight(bounds);

        if (UI::Button(assets, bounds, label.c_str(), 32, background, level > unlocked_count)) {
            scene_manager->GoTo<Level>(level);
        }
        if (level < unlocked_count) {
            SceneVisuals::Sprite(star, bounds.x + MenuGrid::ButtonSize - 20, bounds.y + MenuGrid::ButtonSize - 36, 28);
        }
    }
}

void LevelMenu::Draw() {
    SceneVisuals::Backdrop(assets, MenuGrid::Accent);
    SceneVisuals::Heading(assets, "Levels", Color{240, 235, 215, 255});
    SceneVisuals::Sprite(assets.Get<Texture2D>(Skins::Selected), 120, 150, 64);
    SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::STAR), TotalBoardWidth - 120, 150, 64);

    const int         completed = std::clamp(unlocked_count - 1, 0, level_count);
    const std::string progress  = std::to_string(completed) + " / " + std::to_string(level_count) + " CLEARED";
    UI::CenteredText(assets, TotalBoardWidth / 2.0f, 226, progress.c_str(), 20, MenuGrid::Accent);

    draw_level_buttons();
    MenuGrid::Pager(assets, first_row, level_count);

    if (MenuGrid::SwitchButton(assets, assets.Get<Texture2D>(Skins::Selected))) {
        scene_manager->GoTo<SkinMenu>();
    }
}
