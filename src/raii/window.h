#pragma once
#include "assets.h"
#include "raylib.h"

class Window {
public:
    Window(const int height, const char* title, const int fps) {
        InitWindow(height, height, title);
        SetTargetFPS(fps);

        InitAudioDevice();

        AssetManager::load_assets();
        initialize_background_music();
# ifndef  __EMSCRIPTEN__
        HideCursor();
#endif
    }

    ~Window() {
        AssetManager::unload_assets();
        CloseWindow();
    }

private:
    static void initialize_background_music() {
        const Music& music = AssetManager::Get(MusicAssets::Seaside);

        PlayMusicStream(music);
        SetMusicVolume(music, 0.1f);
    }
};
