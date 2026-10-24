#pragma once
#include <memory>
#include <optional>
#include "scene.h"

enum class SceneType { Opening, Level, Win, Lose };

class SceneManager {
public:
    static SceneManager& Get() {
        static SceneManager instance;
        return instance;
    }

    void Run();
    void GoTo(const SceneType type) { pending = type; }

private:
    void Apply(SceneType type);

    std::unique_ptr<Scene> current;
    std::optional<SceneType> pending;
};