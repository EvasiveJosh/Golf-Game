#ifndef HOSTMULTIPLAYERMENU_H
#define HOSTMULTIPLAYERMENU_H

#include <iostream>
#include "menu.h"
#include "raygui.h"
#include <vector>

enum HostMultiplayerMenuButton
{
    HMMB_Back,
    HMMB_SetUsername,
    HMMB_D_Easy,
    HMMB_D_Medium,
    HMMB_D_Hard,
    HMMB_W_Off,
    HMMB_W_Light,
    HMMB_W_Heavy,
    HMMB_W_Unpredictable,
    HMMB_PL_Limit,
    HMMB_CreateRoom 
};

class HostMultiplayerMenu : public Menu
{
    public:
        HostMultiplayerMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
        std::string getUserName() override;
        std::vector<int> getInformation() override;
    private:
        int usernameLetterCount;
        Rectangle usernameTextBox;
        bool isModifyingUsername;
        char username[MAX_NAME_INPUT + 1] = {0};
        int difficulty;
        int wind;
        int playerLimit;
        void modifyUsername();
        void addButtons();
};

#endif // HOSTMULTIPLAYERMENU_H
