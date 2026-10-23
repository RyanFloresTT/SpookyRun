#pragma once

// Header: only the declaration. What Player is, and what you can call on it.
// Lives in the same folder as player.cpp, always.
struct Grid {
    const int CellCountWidth = 10;
    const int CellSize = 128;

    const int BoardSize = CellCountWidth * CellSize;

    void Draw() const;
};
