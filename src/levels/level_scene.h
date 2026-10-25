#pragma once

#include "../scenes/scene.h"
#include "../scenes/win_scene.h"
#include "../cell.h"

#include "level_manager.h"
#include "../board.h"
#include "../scenes/lost_scene.h"
#include "../ui/button.h"

class Level : public Scene {
public:
    explicit Level(const int level) { this->level = level; }

    void Enter() override {
        LevelManager::LoadLevel(level, playable);
    }

    void Update(const float dt) override {
        playable.Update(dt);

        if (playable.PlayerCaptured()) {
            SceneManager::Get().GoTo<LostScene>(level);
        }

        if (IsKeyPressed(KEY_R)) {
            SceneManager::Get().GoTo<Level>(level);
        }

        if (playable.check_player_win()) {
            LevelManager::SaveProgress(level + 1);
            SceneManager::Get().GoTo<WinScene>();
        }
    }

    static void DrawResetIcon() {
        const Texture2D& repeat_icon = AssetManager::Get(TextureAssets::RepeatIcon);
        constexpr Rectangle r{TotalBoardWidth - 55, TotalBoardWidth - 80, 50.f, 50.f};
        const Rectangle source{0, 0, static_cast<float>(repeat_icon.width), static_cast<float>(repeat_icon.height)};
        DrawTexturePro(repeat_icon, source, r, Vector2{0, 0}, 0.f, WHITE);
    }

    static void DrawResetText() {
        UI::CenteredText(TotalBoardWidth - 75, TotalBoardWidth - 75, "R", 48, WHITE);
    }

    void Draw() override {
        playable.Draw();
        DrawResetIcon();
        DrawResetText();
    }

private:
    Board playable{CellState::Empty};
    int   level;
};
