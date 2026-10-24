#pragma once
#include "raylib.h"
#include "../raii/assets.h"

namespace UI {

    inline bool Button(const Rectangle r, const char* label, const int fontSize = 32) {
        const bool hover   = CheckCollisionPointRec(GetMousePosition(), r);
        const bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        DrawRectangleRec(r, pressed ? DARKGRAY : hover ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(r, 3, BLACK);

        const int w = MeasureText(label, fontSize);
        DrawText(label,
                 static_cast<int>(r.x + (r.width - w) / 2),
                 static_cast<int>(r.y + (r.height - fontSize) / 2),
                 fontSize, BLACK);

        const bool clicked = hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

        if (clicked) {
            PlaySound(AssetManager::GetSound());
        }

        return clicked;
    }

    inline bool CenteredButton(const float centerX, const float y, const char* label,
                               const float w = 240, const float h = 56) {
        return Button(Rectangle{ centerX - w / 2, y, w, h }, label);
    }

    inline void CenteredText(const float centerX, const float y, const char* text,
                             const int size, const Color color) {
        DrawText(text, static_cast<int>(centerX - MeasureText(text, size) / 2.0f),
                 static_cast<int>(y), size, color);
    }

}