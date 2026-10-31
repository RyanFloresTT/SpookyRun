#include "skin_menu.h"
#include "level_menu.h"
#include "lantern/scene/scene_manager.h"
#include "../skins.h"
#include "../ui/button.h"
#include "../ui/menu_grid.h"
#include "../ui/scene_visuals.h"

namespace {
    constexpr int SkinCount = Skins::All.size();
}

SkinMenu::SkinMenu(AssetStore& asset_store) : Scene(asset_store) {
    SceneVisuals::Preload(assets);
    MenuGrid::Preload(assets);
    for (const std::string_view skin : Skins::All) assets.Load<Texture2D>(skin);
    assets.LoadAll<Texture2D>({Assets::UI::BUTTON_BG, Assets::Images::STAR, Assets::UI::TILE_0103});
    assets.Load<Sound>(Assets::SFX::BUTTON_CLICK);
}

void SkinMenu::Update(float) {
    MenuGrid::Scroll(first_row, SkinCount);
}

void SkinMenu::draw_skin_buttons() {
    const Texture2D& background = assets.Get<Texture2D>(Assets::UI::BUTTON_BG);
    const Sound&     click      = assets.Get<Sound>(Assets::SFX::BUTTON_CLICK);

    for (int i = MenuGrid::FirstIndex(first_row); i < MenuGrid::EndIndex(first_row, SkinCount); ++i) {
        const std::string_view skin     = Skins::All[i];
        const Rectangle        bounds   = MenuGrid::Bounds(i, first_row);
        const bool             selected = skin == Skins::Selected;

        if (selected) MenuGrid::Highlight(bounds);

        if (UI::Button(click, bounds, assets.Get<Texture2D>(skin), background, selected)) {
            Skins::Selected = skin;
        }
    }
}

void SkinMenu::Draw() {
    SceneVisuals::Backdrop(assets, MenuGrid::Accent);
    SceneVisuals::Heading(assets, "Skins", Color{240, 235, 215, 255});
    SceneVisuals::Sprite(assets.Get<Texture2D>(Skins::Selected), 120, 150, 64);
    SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::STAR), TotalBoardWidth - 120, 150, 64);

    draw_skin_buttons();
    MenuGrid::Pager(assets, first_row, SkinCount);

    if (MenuGrid::SwitchButton(assets, assets.Get<Texture2D>(Assets::UI::TILE_0103))) {
        scene_manager->GoTo<LevelMenu>();
    }
}
