//
// Created by rryan on 10/25/2026.
//

#include "web_save_manager.h"

#include "raylib.h"


WebSaveManager::WebSaveManager() {
    TraceLog(LOG_INFO, "USING WEB SAVE MANAGER");
}

void WebSaveManager::SaveProgress(int unlocked) {
}

int WebSaveManager::LoadProgress() {
    return 1;
}
