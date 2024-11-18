#ifndef GENERALSETTINGSMENUMENU_H
#define GENERALSETTINGSMENUMENU_H

#include <iostream>
#include "menu.h"
#include "raygui.h"

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
        //For volume
        float volumeLevel;
    public:
        GeneralSettingsMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
        const float& getVolumeLevel() override;
};

#endif