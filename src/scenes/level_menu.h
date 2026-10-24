#pragma once
#include "raylib.h"
#include "scene.h"
#include "scene_manager.h"

#define RAYGUI_IMPLEMENTATION
#include "../../raylib/raygui.h"

class LevelMenu : public Scene {
public:
    void Update(float) override {
    }
    void Draw() override {
        if (GuiButton((Rectangle){ 20, 20, 120, 120 }, "1")) {
            SceneManager::Get().GoTo(SceneType::Level);
        }
    }
};
