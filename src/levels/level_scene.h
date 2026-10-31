#pragma once

#include "lantern/scene/scene.h"
#include "../scenes/win_scene.h"
#include "../cell.h"

#include "level_manager.h"
#include "../assets.h"
#include "../board.h"
#include "../scenes/lost_scene.h"
#include "../ui/button.h"
#include "../config.h"

class Level : public Scene {
public:
    explicit Level(AssetStore& asset_store, const int level) : Scene(asset_store) { this->level = level; }

    void Enter() override {
        LevelManager::LoadLevel(level, playable);
        playable.Enter();
    }

    void Update(const float dt) override {
        playable.Update(dt);

        if (playable.PlayerCaptured()) {
            scene_manager->GoTo<LostScene>(level);
        }

        if (IsKeyPressed(KEY_R)) {
            scene_manager->GoTo<Level>(level);
        }

        if (playable.check_player_win()) {
            LevelManager::SaveProgress(level + 1);
            scene_manager->GoTo<WinScene>();
        }
    }

    void DrawResetIcon() {
        auto repeat_icon = assets.Get<Texture2D>(Assets::UI::ICON_REPEAT_OUTLINE);
        constexpr Rectangle r{TotalBoardWidth - 55, TotalBoardWidth - 80, 50.f, 50.f};
        const Rectangle     source{0, 0, static_cast<float>(repeat_icon.width), static_cast<float>(repeat_icon.height)};
        DrawTexturePro(repeat_icon, source, r, Vector2{0, 0}, 0.f, WHITE);
    }

    void DrawResetText() {
        UI::CenteredText(assets.Get<Font>(Assets::Font::SUPPLY_CENTER_REGULAR), TotalBoardWidth - 75, TotalBoardWidth - 75, "R", 48, WHITE);
    }

    void Draw() override {
        playable.Draw();
        DrawResetIcon();
        DrawResetText();
    }

private:
    Board playable{asset_store, CellState::Empty};
    int   level;
};
