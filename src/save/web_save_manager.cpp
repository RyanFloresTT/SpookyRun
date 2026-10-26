//
// Created by rryan on 10/25/2026.
//

#include "web_save_manager.h"

#include <algorithm>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

EM_JS(int, LoadWebProgress, (),  {
    try {
        const saved
        =
        localStorage.getItem("solojam.progress");
        if (saved == = null) return 1;

        const data
        =
        JSON.parse(saved);
        if (data&& Number
        .
        isInteger(data.unlocked) &&
            data.unlocked >= 1 && data.unlocked <= 2147483647
        )
        {
            return data.unlocked;
        }
    }
    catch (error) {
        console.warn("Could not load Solojam progress.", error);
    }
    return 1;
});

EM_JS(void, SaveWebProgress, (int unlocked),  {
    try {
        localStorage.setItem("solojam.progress", JSON.stringify({unlocked: unlocked}));
    }
    catch (error) {
        console.warn("Could not save Solojam progress; progress will last for this session only.", error);
    }
});
#endif

void WebSaveManager::SaveProgress(int unlocked) {
    if (unlocked <= LoadProgress()) return;

    unlocked_progress = unlocked;
#ifdef __EMSCRIPTEN__
    SaveWebProgress(unlocked_progress);
#endif
}

int WebSaveManager::LoadProgress() {
#ifdef __EMSCRIPTEN__
    unlocked_progress = std::max(unlocked_progress, LoadWebProgress());
#endif
    return unlocked_progress;
}
