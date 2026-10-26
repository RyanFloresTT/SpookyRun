#include "level_menu.h"
#include "scene_manager.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"

void LevelMenu::Enter() {
    levelCount     = LevelManager::GetLevelCount();
    unlocked_count = LevelManager::LoadProgress();
    firstRow       = 0;
}

void LevelMenu::Update(float) {
    const int   rowCount  = (levelCount + Columns - 1) / Columns;
    const float wheel     = GetMouseWheelMove();
    const int   direction = wheel > 0 ? -1 : wheel < 0 ? 1 : 0;
    firstRow              = std::clamp(firstRow + direction, 0, std::max(0, rowCount - VisibleRows));
}

void LevelMenu::draw_character_skin_toggle() {
    const Texture2D& icon = character_screen_open ? AssetManager::Get(TextureAssets::Sword) : AssetManager::Get(TextureAssets::Player);
    constexpr Rectangle r{TotalBoardWidth - 120, TotalBoardWidth - 120, 100.f, 100.f};
    if (UI::Button(r, icon, AssetManager::Get(TextureAssets::WhiteButton))) {
        character_screen_open = !character_screen_open;
        title_text            = character_screen_open ? "Skins" : "Levels";
    }
}

void LevelMenu::draw_level_buttons() const {
    const int firstLevel = firstRow * Columns + 1;
    const int lastLevel  = std::min(levelCount, (firstRow + VisibleRows) * Columns);
    for (int level = firstLevel; level <= lastLevel; ++level) {
        const int         index = level - firstLevel;
        const float       x     = Padding + (index % Columns) * (ButtonSize + Spacing);
        const float       y     = Padding + (index / Columns) * (ButtonSize + Spacing);
        const std::string label = std::to_string(level);
        if (!character_screen_open && UI::Button(Rectangle{x, y, ButtonSize, ButtonSize}, label.c_str(), 32,
                                                 AssetManager::Get(TextureAssets::ButtonBackground), level > unlocked_count)) {
            SceneManager::Get().GoTo<Level>(level);
        }
    }
}

void LevelMenu::render_player_skin_buttons() {
    const int skinCount = AssetManager::GetAlternateSkinCount();
    const int firstSkin = firstRow * Columns;
    const int lastSkin  = std::min(skinCount, (firstRow + VisibleRows) * Columns);

    for (int i = firstSkin; i < lastSkin; ++i) {
        const int   index = i - firstSkin;
        const float x     = Padding + (index % Columns) * (ButtonSize + Spacing);
        const float y     = Padding + (index / Columns) * (ButtonSize + Spacing);

        const AlternateSkinAssets skin = AssetManager::GetAlternateSkinKey(i);

        if (UI::Button(Rectangle{x, y, ButtonSize, ButtonSize},
                       AssetManager::Get(skin),
                       AssetManager::Get(TextureAssets::ButtonBackground), skin == selected_skin)) {
                            selected_skin = skin;
                            AssetManager::SwapPlayerSkin(skin);
                       }
    }
}

void LevelMenu::Draw() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BEIGE);

    UI::CenteredText(TotalBoardWidth / 2.0f, TotalBoardWidth / 2.0f - 900 / 2.0f, title_text.c_str(), 96, BLACK);

    if (character_screen_open) {
        render_player_skin_buttons();
    } else {
        draw_level_buttons();
    }

    // Character Selection Toggle
    draw_character_skin_toggle();
}
