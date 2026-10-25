#include "level_menu.h"
#include "scene_manager.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"

void LevelMenu::Enter() {
    levelCount = LevelManager::GetLevelCount();
    unlocked_count = LevelManager::LoadProgress();
    firstRow   = 0;
}

void LevelMenu::Update(float) {
    const int   rowCount  = (levelCount + Columns - 1) / Columns;
    const float wheel     = GetMouseWheelMove();
    const int   direction = wheel > 0 ? -1 : wheel < 0 ? 1 : 0;
    firstRow              = std::clamp(firstRow + direction, 0, std::max(0, rowCount - VisibleRows));
}

void LevelMenu::Draw() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BEIGE);

    const int firstLevel = firstRow * Columns + 1;
    const int lastLevel  = std::min(levelCount, (firstRow + VisibleRows) * Columns);
    for (int level = firstLevel; level <= lastLevel; ++level) {
        const int         index = level - firstLevel;
        const float       x     = Padding + (index % Columns) * (ButtonSize + Spacing);
        const float       y     = Padding + (index / Columns) * (ButtonSize + Spacing);
        const std::string label = std::to_string(level);
        if (UI::Button(Rectangle{x, y, ButtonSize, ButtonSize}, label.c_str(), 32, AssetManager::GetButtonBackground(), level > unlocked_count)) {
            SceneManager::Get().GoTo<Level>(level);
        }
    }

    constexpr Rectangle r{TotalBoardWidth - 120, TotalBoardWidth - 120, 100.f, 100.f};
    UI::Button(r, AssetManager::GetTexture(PieceType::Pawn), AssetManager::GetButtonBackground());
}
