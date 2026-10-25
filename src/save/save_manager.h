#pragma once

class SaveManager {
public:
        virtual ~SaveManager() = default;
        virtual void SaveProgress(int unlocked) = 0;
        virtual int LoadProgress() = 0;
};