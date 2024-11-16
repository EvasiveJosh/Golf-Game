#ifndef SINGLEPLAYERGAMESETTINGSMENU_H
#define SINGLEPLAYERGAMESETTINGSMENU_H

#include "menu.h"
#include <iostream>

enum SingleplayerGameSettingsMenuButton
{
    SGSMB_Back,
    SGSMB_Start,
    SGSMB_D_Easy,
    SGSMB_D_Medium,
    SGSMB_D_Hard,
    SGSMB_W_Off,
    SGSMB_W_Light,
    SGSMB_W_Heavy,
    SGSMB_W_Unpredictable,
    SGSMB_EM_Off,
    SGSMB_EM_On
};

class SingleplayerGameSettingsMenu : public Menu
{
    private:
        int difficulty; //0 to 2 (easy, medium, hard)
        int wind; //0 to 3 (off, light, heavy, unpredictable)
        int endlessmode; //0 to 1 (off, on)
    public:
        SingleplayerGameSettingsMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
        std::vector<int> getInformation() override;
};

#endif