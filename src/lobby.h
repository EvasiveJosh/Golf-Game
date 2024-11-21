#ifndef LOBBY_H
#define LOBBY_H

#include "menu.h"
#include <vector>
#include <string>

enum LobbyMenuButton
{
    LMB_Back,
    LMB_StartGame
};

class Lobby : public Menu
{
    private:
        std::string hostUsername;
        std::vector<int> gameSettings;
        int playerLimit;
        std::vector<std::string> connectedPlayers; // For future multiplayer implementation

    public:
        Lobby(const std::string& username, const std::vector<int>& settings, int maxPlayers);
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
        
    private:
        void addButtons();
};

#endif
