#pragma once
#include "scene.h"
#include "../board.h"
#include "../cell.h"

class LostScene : public Scene {
public:
    explicit LostScene(const int retryLevel) : retry_level(retryLevel) {}

    void Update(float) override {}
    void Draw() override;

private:
    Board background{CellState::Empty};
    int   retry_level;
};
