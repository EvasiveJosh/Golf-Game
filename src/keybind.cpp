#include "Keybind.h"

// Define the global Keybind object
Keybind keybinds;

// Constructor
Keybind::Keybind() {
    InitializeDefaultKeybinds();
}

// Initialize default keybinds
void Keybind::InitializeDefaultKeybinds() {
    keyMap["CamUp"] = KEY_W;
    keyMap["CamDown"] = KEY_S;
    keyMap["CamLeft"] = KEY_A;
    keyMap["CamRight"] = KEY_D;
    keyMap["CamCenter"] = KEY_C;
    keyMap["CamFollow"] = KEY_F;
    keyMap["Pause"] = KEY_GRAVE;
    keyMap["Debug"] = KEY_COMMA;
}

// Set a new key for a specific action
void Keybind::SetKey(const std::string& action, int newKey) {
    if (keyMap.find(action) != keyMap.end()) {
        keyMap[action] = newKey;
    }
}

// Get the current key for a specific action
int Keybind::GetKey(const std::string& action) const {
    auto it = keyMap.find(action);
    if (it != keyMap.end()) {
        return it->second;
    }
    return -1; // Return an invalid key if the action is not found
}

// Check if the key for a specific action is pressed
bool Keybind::IsPressed(const std::string& action) const {
    int key = GetKey(action);
    return key != -1 && IsKeyPressed(key);
}

// Check if the key for a specific action is down
bool Keybind::IsDown(const std::string& action) const {
    int key = GetKey(action);
    return key != -1 && IsKeyDown(key);
}
