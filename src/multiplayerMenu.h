#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <iostream>
#include "menu.h"

enum MultiplayerMenuButton
{
    MMB_Back,
    MMB_Host,
    MMB_Join
};

class MultiplayerMenu : public Menu
{
    public:
        MultiplayerMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
};

#endif