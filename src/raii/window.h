#pragma once
#include "assets.h"
#include "raylib.h"

class Window {
public:
    Window(const int height, const char* title, const int fps) {
        InitWindow(height, height, title);
        SetTargetFPS(fps);
        AssetManager::LoadTextures();
    }
    ~Window() {
        AssetManager::UnloadTextures();
        CloseWindow();
    }
};