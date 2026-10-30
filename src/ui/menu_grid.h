#pragma once
#include <algorithm>
#include <string>

#include "button.h"
#include "../config.h"

// Shared layout for the paged button grids on the level and skin menus.
namespace MenuGrid {
    inline constexpr int   Padding     = 175;
    inline constexpr int   GridTop     = 260;
    inline constexpr int   ButtonSize  = 120;
    inline constexpr int   Spacing     = 30;
    inline constexpr int   Columns     = (TotalBoardWidth - 2 * Padding + Spacing) / (ButtonSize + Spacing);
    inline constexpr int   VisibleRows = 3;
    inline constexpr Color Accent{226, 190, 92, 255};

    inline int FirstIndex(const int first_row) { return first_row * Columns; }
    inline int EndIndex(const int first_row, const int item_count) {
        return std::min(item_count, (first_row + VisibleRows) * Columns);
    }

    inline int MaxFirstRow(const int item_count) {
        const int row_count = (item_count + Columns - 1) / Columns;
        return std::max(0, row_count - VisibleRows);
    }

    // Bounds of the button for the item at `index`, given the first visible row.
    inline Rectangle Bounds(const int index, const int first_row) {
        const int   slot = index - FirstIndex(first_row);
        const float x    = Padding + static_cast<float>(slot % Columns) * (ButtonSize + Spacing);
        const float y    = GridTop + static_cast<float>(slot / Columns) * (ButtonSize + Spacing);
        return Rectangle{x, y, ButtonSize, ButtonSize};
    }

    inline void Highlight(const Rectangle r) {
        DrawRectangleLinesEx(Rectangle{r.x - 4, r.y - 4, r.width + 8, r.height + 8}, 3, Accent);
    }

    inline void Scroll(int& first_row, const int item_count) {
        const float wheel     = GetMouseWheelMove();
        const int   direction = wheel > 0 ? -1 : wheel < 0 ? 1 : 0;
        first_row             = std::clamp(first_row + direction, 0, MaxFirstRow(item_count));
    }

    // Page arrows and the "x - y" range label. Draws nothing when everything fits on one page.
    inline void Pager(AssetStore& assets, int& first_row, const int item_count) {
        const int max_first_row = MaxFirstRow(item_count);
        if (max_first_row == 0) return;

        const Texture2D& background = assets.Get<Texture2D>(Assets::UI::BUTTON_SQUARE_DEPTH_LINE);
        if (UI::Button(assets, Rectangle{Padding, 718, 64, 64}, "<", 32, background, first_row == 0)) {
            first_row = std::max(0, first_row - VisibleRows);
        }
        if (UI::Button(assets, Rectangle{TotalBoardWidth - Padding - 64, 718, 64, 64}, ">", 32,
                       background, first_row == max_first_row)) {
            first_row = std::min(max_first_row, first_row + VisibleRows);
        }
        const std::string range = std::to_string(FirstIndex(first_row) + 1) + " - " +
            std::to_string(EndIndex(first_row, item_count));
        UI::CenteredText(assets, TotalBoardWidth / 2.0f, 738, range.c_str(), 24, Accent);
    }

    // Square button in the bottom-right corner used to switch between the level and skin menus.
    inline bool SwitchButton(AssetStore& assets, const Texture2D& icon) {
        constexpr Rectangle r{TotalBoardWidth - 180, 718, 64.f, 64.f};
        return UI::Button(assets, r, icon, assets.Get<Texture2D>(Assets::UI::BUTTON_SQUARE_DEPTH_LINE));
    }
}
