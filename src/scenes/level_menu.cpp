#include "level_menu.h"
#include "lantern/scene/scene_manager.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"
#include "../ui/scene_visuals.h"

void LevelMenu::Enter() {
    levelCount     = LevelManager::GetLevelCount();
    unlocked_count = LevelManager::LoadProgress();
    firstRow       = 0;
}

void LevelMenu::Update(float) {
    const int   itemCount = character_screen_open ? AssetManager::GetAlternateSkinCount() : levelCount;
    const int   rowCount  = (itemCount + Columns - 1) / Columns;
    const float wheel     = GetMouseWheelMove();
    const int   direction = wheel > 0 ? -1 : wheel < 0 ? 1 : 0;
    firstRow              = std::clamp(firstRow + direction, 0, std::max(0, rowCount - VisibleRows));
}

void LevelMenu::draw_character_skin_toggle() {
    const Texture2D& icon = character_screen_open
                                ? AssetManager::Get(TextureAssets::Sword)
                                : AssetManager::Get(TextureAssets::Player);
    constexpr Rectangle r{TotalBoardWidth - 180, 718, 64.f, 64.f};
    if (UI::Button(r, icon, AssetManager::Get(TextureAssets::WhiteButton))) {
        character_screen_open = !character_screen_open;
        title_text            = character_screen_open ? "Skins" : "Levels";
        firstRow              = 0;
    }
}

void LevelMenu::draw_level_buttons() const {
    const int firstLevel = firstRow * Columns + 1;
    const int lastLevel  = std::min(levelCount, (firstRow + VisibleRows) * Columns);
    for (int level = firstLevel; level <= lastLevel; ++level) {
        const int         index = level - firstLevel;
        const float       x     = Padding + (index % Columns) * (ButtonSize + Spacing);
        const float       y     = GridTop + (index / Columns) * (ButtonSize + Spacing);
        const std::string label = std::to_string(level);
        const Rectangle   bounds{x, y, ButtonSize, ButtonSize};
        if (level == unlocked_count) {
            DrawRectangleLinesEx(Rectangle{x - 4, y - 4, ButtonSize + 8, ButtonSize + 8}, 3,
                                 Color{226, 190, 92, 255});
        }
        if (!character_screen_open && UI::Button(bounds, label.c_str(), 32,
                                                 AssetManager::Get(TextureAssets::ButtonBackground),
                                                 level > unlocked_count)) {
            SceneManager::Get().GoTo<Level>(level);
        }
        if (level < unlocked_count) {
            SceneVisuals::Sprite(TextureAssets::Star, x + ButtonSize - 20, y + ButtonSize - 36, 28);
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
        const float y     = GridTop + (index / Columns) * (ButtonSize + Spacing);

        const AlternateSkinAssets skin = AssetManager::GetAlternateSkinKey(i);

        if (skin == selected_skin) {
            DrawRectangleLinesEx(Rectangle{x - 4, y - 4, ButtonSize + 8, ButtonSize + 8}, 3,
                                 Color{226, 190, 92, 255});
        }
        if (UI::Button(Rectangle{x, y, ButtonSize, ButtonSize},
                       AssetManager::Get(skin),
                       AssetManager::Get(TextureAssets::ButtonBackground), skin == selected_skin)) {
            selected_skin = skin;
            AssetManager::SwapPlayerSkin(skin);
        }
    }
}

void LevelMenu::Draw() {
    constexpr Color accent{226, 190, 92, 255};
    SceneVisuals::Backdrop(accent);
    SceneVisuals::Heading(title_text.c_str(), Color{240, 235, 215, 255});
    SceneVisuals::Sprite(TextureAssets::Player, 120, 150, 64);
    SceneVisuals::Sprite(TextureAssets::Star, TotalBoardWidth - 120, 150, 64);

    if (!character_screen_open) {
        const int         completed = std::clamp(unlocked_count - 1, 0, levelCount);
        const std::string progress  = std::to_string(completed) + " / " + std::to_string(levelCount) + " CLEARED";
        UI::CenteredText(TotalBoardWidth / 2.0f, 226, progress.c_str(), 20, accent);
    }

    if (character_screen_open) {
        render_player_skin_buttons();
    }
    else {
        draw_level_buttons();
    }

    const int itemCount   = character_screen_open ? AssetManager::GetAlternateSkinCount() : levelCount;
    const int rowCount    = (itemCount + Columns - 1) / Columns;
    const int maxFirstRow = std::max(0, rowCount - VisibleRows);
    if (maxFirstRow > 0) {
        const Texture2D& background = AssetManager::Get(TextureAssets::WhiteButton);
        if (UI::Button(Rectangle{Padding, 718, 64, 64}, "<", 32, background, firstRow == 0)) {
            firstRow = std::max(0, firstRow - VisibleRows);
        }
        if (UI::Button(Rectangle{TotalBoardWidth - Padding - 64, 718, 64, 64}, ">", 32,
                       background, firstRow == maxFirstRow)) {
            firstRow = std::min(maxFirstRow, firstRow + VisibleRows);
        }
        const std::string range = std::to_string(firstRow * Columns + 1) + " - " +
            std::to_string(std::min(itemCount, (firstRow + VisibleRows) * Columns));
        UI::CenteredText(TotalBoardWidth / 2.0f, 738, range.c_str(), 24, accent);
    }

    draw_character_skin_toggle();
}
