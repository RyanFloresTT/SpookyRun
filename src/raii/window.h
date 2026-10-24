#pragma once
#include "assets.h"
#include "raylib.h"

class Window {
public:
    Window(const int height, const char* title, const int fps) {
        InitWindow(height, height, title);
        SetTargetFPS(fps);
        AssetManager::load_assets();
        AssetManager::PlayMusic();
    }
    ~Window() {
        AssetManager::unload_assets();
        CloseWindow();
    }
};