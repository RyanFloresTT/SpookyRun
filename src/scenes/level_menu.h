#pragma once
#include "raylib.h"
#include "scene.h"
#include "scene_manager.h"
#include "../levels/level_scene.h"

class LevelMenu : public Scene {
public:
    void Update(float) override {}

    void Draw() override {
        if (Button(Rectangle{ 20, 20, 120, 120 }, "1")) {
            SceneManager::Get().GoTo<Level>(1);
        }
    }

private:
    static bool Button(Rectangle r, const char* label);
};

inline bool LevelMenu::Button(const Rectangle r, const char* label) {
    const bool hover   = CheckCollisionPointRec(GetMousePosition(), r);
    const bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    DrawRectangleRec(r, pressed ? DARKGRAY : hover ? GRAY : LIGHTGRAY);
    DrawRectangleLinesEx(r, 3, BLACK);

    constexpr int fontSize = 48;
    const int     w        = MeasureText(label, fontSize);
    DrawText(label,
             static_cast<int>(r.x + (r.width - w) / 2),
             static_cast<int>(r.y + (r.height - fontSize) / 2),
             fontSize, BLACK);

    return hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
