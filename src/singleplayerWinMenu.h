#ifndef SINGLEPLAYERWINMENU_H
#define SINGLEPLAYERWINMENU_H

#include "menu.h"
#include <iostream>

class SingleplayerWinMenu : public Menu
{
    public:
        SingleplayerWinMenu(int shotCount);
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;

    private:
        int shotCount;
        void addButtons();
};

enum SingleplayerWinMenuButton
{
    SWMB_Restart,
    SWMB_Exit
};

#endif