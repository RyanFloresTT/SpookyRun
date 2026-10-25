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
    void Draw() override;

private:
    static constexpr int Padding     = 100;
    static constexpr int ButtonSize  = 160;
    static constexpr int Spacing     = 60;
    static constexpr int Columns     = (TotalBoardWidth - 2 * Padding + Spacing) / (ButtonSize + Spacing);
    static constexpr int VisibleRows = Columns;

    int levelCount = 0;
    int firstRow   = 0;
    int unlocked_count = 0;

    std::unique_ptr<SaveManager> save_manager;
};
