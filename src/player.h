#pragma once

class Grid;

class Player {
public:
    Player(const int startX, const int startY, Grid& PlayableGrid) : PlayableGrid(PlayableGrid), x(startX), y(startY) {}
    void Move(int dx, int dy);
    void Init() const;
    bool PlayerWon() const;

private:
    Grid& PlayableGrid;
    int x, y;
};
