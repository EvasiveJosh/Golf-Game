#ifndef SINGLEPLAYERWINMENU_H
#define SINGLEPLAYERWINMENU_H

#include "menu.h"
#include <iostream>

enum SingleplayerWinMenuButton
{
    SWMB_Exit
};

class SingleplayerWinMenu : public Menu
{
    public:
        SingleplayerWinMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
};

#endif