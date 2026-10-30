#pragma once
#include <cmath>

#include "raylib.h"
#include "../assets.h"
#include "lantern/assets/asset_store.h"

namespace UI {
    inline void CenteredText(AssetStore& assets, const float centerX, const float y, const char* text,
                             const int   size, const Color    color) {
        const Font&     font    = assets.Get<Font>(Assets::Font::SUPPLY_CENTER_REGULAR);
        constexpr float spacing = 0.0f;

        const Vector2 measured = MeasureTextEx(font, text, static_cast<float>(size), spacing);
        const Vector2 pos{
            std::floor(centerX - measured.x / 2.0f),
            std::floor(y)
        };

        DrawTextEx(font, text, pos, static_cast<float>(size), spacing, color);
    }

    inline bool Clicked(AssetStore& assets, const bool hover) {
        const bool clicked = hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        if (clicked) {
            PlaySound(assets.Get<Sound>(Assets::SFX::BUTTON_CLICK));
        }
        return clicked;
    }

    inline bool Button(AssetStore& assets, const Rectangle r, const char* label, const int fontSize) {
        const bool hover   = CheckCollisionPointRec(GetMousePosition(), r);
        const bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        DrawRectangleRec(r, pressed ? DARKGRAY : hover ? GRAY : LIGHTGRAY);
        DrawRectangleLinesEx(r, 3, BLACK);

        CenteredText(assets, r.x + r.width / 2, r.y + (r.height - fontSize) / 2, label, fontSize, BLACK);

        return Clicked(assets, hover);
    }

    inline bool Button(AssetStore& assets, const Rectangle r, const char* label, const int fontSize,
                       const Texture2D& background, const bool locked = false) {
        const bool hover   = CheckCollisionPointRec(GetMousePosition(), r);
        const bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        const auto tint = locked ? DARKGRAY : pressed ? DARKGRAY : hover ? GRAY : LIGHTGRAY;

        const Rectangle source{0, 0, static_cast<float>(background.width), static_cast<float>(background.height)};

        DrawTexturePro(background, source, r, Vector2{0, 0}, 0.f, tint);

        CenteredText(assets, r.x + r.width / 2, r.y + (r.height - fontSize) / 2, label, fontSize, BLACK);

        if (locked) return false;

        return Clicked(assets, hover);
    }

    inline bool Button(AssetStore& assets, const Rectangle r, const Texture2D& icon, const Texture2D& background,
                       const bool  locked = false, const float pad = 0.15f) {
        const bool hover   = CheckCollisionPointRec(GetMousePosition(), r);
        const bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        const auto tint = locked ? DARKGRAY : pressed ? DARKGRAY : hover ? GRAY : LIGHTGRAY;

        const Rectangle bg_source{0, 0, static_cast<float>(background.width), static_cast<float>(background.height)};
        const Rectangle icon_source{0, 0, static_cast<float>(icon.width), static_cast<float>(icon.height)};

        const float     padding = r.width * pad;
        const Rectangle iconDest{r.x + padding, r.y + padding, r.width - padding * 2, r.height - padding * 2};

        DrawTexturePro(background, bg_source, r, Vector2{0, 0}, 0.f, tint);
        DrawTexturePro(icon, icon_source, iconDest, Vector2{0, 0}, 0.f, tint);

        if (locked) return false;

        return Clicked(assets, hover);
    }

    inline bool CenteredButton(AssetStore& assets, const float centerX, const float y, const char* label,
                               const float w = 240, const float h = 56) {
        return Button(assets, Rectangle{centerX - w / 2, y, w, h}, label, 32);
    }
}
