// level_menu.h
#pragma once
#include "scene.h"
#include "../board.h"
#include "../cell.h"

class LevelMenu : public Scene {
public:
    void Enter() override;
    void Update(float) override;
    void Draw() override;
private:
    static constexpr int Padding = 20;
    static constexpr int ButtonSize = 120;
    static constexpr int Spacing = 20;
    static constexpr int Columns = (TotalBoardWidth - 2 * Padding + Spacing) / (ButtonSize + Spacing);
    static constexpr int VisibleRows = Columns;

    int levelCount = 0;
    int firstRow = 0;
    Board background{CellState::Empty};
};