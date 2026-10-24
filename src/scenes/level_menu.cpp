#include "level_menu.h"
#include "scene_manager.h"
#include "../levels/level_scene.h"
#include "../ui/button.h"

void LevelMenu::Draw() {
    background.Draw();
    if (UI::Button(Rectangle{ 20, 20, 120, 120 }, "1")) {
        SceneManager::Get().GoTo<Level>(1);
    }
}