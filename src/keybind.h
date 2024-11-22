#ifndef KEYBIND_H
#define KEYBIND_H

#include <raylib.h>
#include <string>
#include <unordered_map>

class Keybind {
public:
    Keybind();

    void SetKey(const std::string& action, int newKey);
    int GetKey(const std::string& action) const;
    bool IsPressed(const std::string& action) const;
    bool IsDown(const std::string& action) const;

private:
    std::unordered_map<std::string, int> keyMap;
    void InitializeDefaultKeybinds();
};

// Declare a global Keybind object
extern Keybind keybinds;

#endif // KEYBIND_H
