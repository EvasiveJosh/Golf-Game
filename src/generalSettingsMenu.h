#ifndef GENERALSETTINGSMENUMENU_H
#define GENERALSETTINGSMENUMENU_H

#include <iostream>
#include "menu.h"

enum GeneralSettingsMenuButton
{
    GSMB_Back,
    GSMB_480p,
    GSMB_720p,
    GSMB_1080p,
    GSMB_1440p,
    GSMB_3840p
};

class GeneralSettingsMenu : public Menu
{
    private:
        //Assuming 16:9 aspect ratio
        bool currentResolution[5];
    public:
        GeneralSettingsMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
};

#endif