// level_menu.h
#pragma once
#include "scene.h"
#include "../board.h"
#include "../cell.h"
#include "../save/save_manager.h"

class LevelMenu : public Scene {
public:
    void Enter() override;
    void Update(float) override;
    void draw_character_skin_toggle();
    void draw_level_buttons() const;
    void render_player_skin_buttons();
    void Draw() override;

private:
    static constexpr int Padding     = 160;
    static constexpr int ButtonSize  = 120;
    static constexpr int Spacing     = 30;
    static constexpr int Columns     = (TotalBoardWidth - 2 * Padding + Spacing) / (ButtonSize + Spacing);
    static constexpr int VisibleRows = Columns;

    int levelCount     = 0;
    int firstRow       = 0;
    int unlocked_count = 1;

    std::string title_text = "Levels";

    bool                character_screen_open = false;
    AlternateSkinAssets selected_skin = AlternateSkinAssets::Monk;
};
