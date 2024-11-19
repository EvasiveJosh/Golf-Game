#ifndef SINGLEPLAYERPAUSEMENU_H
#define SINGLEPLAYERPAUSEMENU_H

#include "menu.h"
#include <iostream>

class SingleplayerPauseMenu : public Menu
{
public:
    SingleplayerPauseMenu();
    void draw() override;
    GuiEvent updateMenuLogic() override;
    void drawDebug() override;

private:
    void addButtons();
};

enum SingleplayerPauseMenuButton
{
    SPMB_Resume,
    SPMB_ReturnToStart
};

#endif