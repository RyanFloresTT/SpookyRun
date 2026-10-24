#pragma once
#include "raylib.h"
#include "scene.h"
#include "scene_manager.h"
#include "../board.h"
#include "../cell.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"

class LevelMenu : public Scene {
public:
    void Update(float) override {}

    void Draw() override {
        background.Draw();

        if (UI::Button(Rectangle{ 20, 20, 120, 120 }, "1")) {
            SceneManager::Get().GoTo<Level>(1);
        }
    }

private:
    Board background{CellState::Empty};
};