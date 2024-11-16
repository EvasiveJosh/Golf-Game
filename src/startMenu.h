#ifndef STARTMENU_H
#define STARTMENU_H

#include "menu.h"
#include <iostream>

enum StartMenuButton
{
    SMB_Singleplayer,
    SMB_Multiplayer,
    SMB_Settings,
    SMB_Exit
};

class StartMenu : public Menu
{
    public:
        StartMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
};

#endif