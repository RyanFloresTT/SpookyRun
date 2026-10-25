#pragma once
#include "raylib.h"
#include "../raii/assets.h"

namespace UI {
    inline bool Button(const Rectangle r, const char* label, const int fontSize) {
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
            PlaySound(AssetManager::Get(SFXAssets::ButtonClick));
        }

        return clicked;
    }

    inline bool Button(const Rectangle r, const char* label, const int fontSize, const Texture2D& background, const bool locked = false) {
        const bool hover   = CheckCollisionPointRec(GetMousePosition(), r);
        const bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        const auto tint = locked ? DARKGRAY : pressed ? DARKGRAY : hover ? GRAY : LIGHTGRAY;

        const Rectangle source{0, 0, static_cast<float>(background.width), static_cast<float>(background.height)};

        DrawTexturePro(background, source, r, Vector2{0, 0}, 0.f, tint);

        const int w = MeasureText(label, fontSize);
        DrawText(label,
                 static_cast<int>(r.x + (r.width - w) / 2),
                 static_cast<int>(r.y + (r.height - fontSize) / 2),
                 fontSize, BLACK);

        if (locked) return false;

        const bool clicked = hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

        if (clicked) {
            PlaySound(AssetManager::Get(SFXAssets::ButtonClick));
        }

        return clicked;
    }

    inline bool Button(const Rectangle r, const Texture2D& icon, const Texture2D& background, const bool locked = false) {
        const bool hover   = CheckCollisionPointRec(GetMousePosition(), r);
        const bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        const auto tint = locked ? DARKGRAY : pressed ? DARKGRAY : hover ? GRAY : LIGHTGRAY;

        const Rectangle source{0, 0, static_cast<float>(background.width), static_cast<float>(background.height)};

        DrawTexturePro(background, source, r, Vector2{0, 0}, 0.f, tint);
        DrawTexturePro(icon, source, r, Vector2{0, 0}, 0.f, tint);

        if (locked) return false;

        const bool clicked = hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

        if (clicked) {
            PlaySound(AssetManager::Get(SFXAssets::ButtonClick));
        }

        return clicked;
    }

    inline bool CenteredButton(const float centerX, const float y, const char* label,
                               const float w = 240, const float h = 56) {
        return Button(Rectangle{centerX - w / 2, y, w, h}, label, 32);
    }

    inline void CenteredText(const float centerX, const float y, const char* text,
                             const int   size, const Color    color) {
        const Font&     font    = AssetManager::Get(FontAssets::SupplyCenter);
        constexpr float spacing = 0.0f;

        const Vector2 measured = MeasureTextEx(font, text, static_cast<float>(size), spacing);
        const Vector2 pos{
            std::floor(centerX - measured.x / 2.0f),
            std::floor(y)
        };

        DrawTextEx(font, text, pos, static_cast<float>(size), spacing, color);
    }
}
