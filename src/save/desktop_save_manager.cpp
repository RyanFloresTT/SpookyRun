//
// Created by rryan on 10/25/2026.
//

#include "desktop_save_manager.h"
#include "raylib.h"

#include <fstream>
#include <nlohmann/json.hpp>

void DesktopSaveManager::SaveProgress(int unlocked) {
    if (unlocked <= LoadProgress()) return;

    const nlohmann::json new_data = {{"unlocked", unlocked}};

    std::ofstream file("assets/data/save.json");
    if (!file) {
        TraceLog(LOG_ERROR, "Could not open save.json to write to it");
        return;
    }

    file << new_data;
}

int  DesktopSaveManager::LoadProgress() {
    // ideally I would wrap this so we could load data easily, this is replicated code from level manager
    std::ifstream file("assets/data/save.json");
    if (!file) {
        TraceLog(LOG_ERROR, "Could not open save.json");
        return 0;
    }

    const nlohmann::json data = nlohmann::json::parse(file, nullptr, false);
    if (data.is_discarded()) {
        TraceLog(LOG_ERROR, "save.json is not valid JSON");
        return 0;
    }

    const nlohmann::json size = data.value("unlocked", nlohmann::json(0));
    return size.get<int>();
}
