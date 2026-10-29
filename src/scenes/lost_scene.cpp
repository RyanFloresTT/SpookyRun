#include "lost_scene.h"
#include "level_menu.h"
#include "opening_scene.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"
#include "../ui/scene_visuals.h"
#include "lantern/scene/scene_manager.h"

void LostScene::Draw() {
    constexpr Color accent{226, 133, 139, 255};
    const float center_x = GetScreenWidth() / 2.0f;
    const float height = static_cast<float>(GetScreenHeight());
    SceneVisuals::Backdrop(accent);
    SceneVisuals::Heading("You Lost!", accent);

    SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::ROOK), center_x - 112, height * 0.32f, 96);
    SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::BISHOP), center_x + 112, height * 0.32f, 96);
    SceneVisuals::Sprite(assets.Get<Texture2D>(Assets::Images::MONK), center_x, height * 0.37f, 88, Color{161, 161, 161, 255});
    DrawLineEx(Vector2{center_x - 36, height * 0.48f}, Vector2{center_x + 36, height * 0.48f}, 3, accent);

    Rectangle r{center_x - 120, height * 0.55f, 240, 56};
    if (UI::Button(r,"Try Again", 24, assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE))) scene_manager->GoTo<Level>(retry_level);

    r.y += height * 0.08f;
    if (UI::Button(r,"Level Menu", 24, assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE))) scene_manager->GoTo<LevelMenu>();

    r.y += height * 0.08f;
    if (UI::Button(r,"Main Menu", 24, assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE))) scene_manager->GoTo<OpeningScene>();

    r.y += height * 0.08f;
    if (UI::Button(r,"Quit", 24, assets.Get<Texture2D>(Assets::UI::BUTTON_RECTANGLE_DEPTH_LINE))) scene_manager->Quit();
}
