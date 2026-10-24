// level_menu.h
#pragma once
#include "scene.h"
#include "../board.h"
#include "../cell.h"

class LevelMenu : public Scene {
public:
    void Update(float) override {}
    void Draw() override;
private:
    Board background{CellState::Empty};
};