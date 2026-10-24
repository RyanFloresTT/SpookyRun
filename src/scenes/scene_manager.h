#pragma once
#include <functional>
#include <memory>
#include "scene.h"

class SceneManager {
public:
    static SceneManager& Get() {
        static SceneManager instance;
        return instance;
    }

    static void display_cursor();
    void        Run();
    void Quit() { running = false; }

    template <typename T, typename... Args>
    void GoTo(Args... args) {
        pending = [=] { return std::make_unique<T>(args...); };
    }

private:
    std::unique_ptr<Scene>                  current;
    std::function<std::unique_ptr<Scene>()> pending;
    bool running = true;
};