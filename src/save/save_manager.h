#pragma once

class SaveManager {
protected:
    ~SaveManager() = default;

public:
    virtual void Save() = 0;
    virtual void Load() = 0;
};