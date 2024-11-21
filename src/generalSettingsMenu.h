#ifndef GENERALSETTINGSMENUMENU_H
#define GENERALSETTINGSMENUMENU_H

#include <iostream>
#include "menu.h"
#include "raygui.h"
#include "userSettings.h"

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
        //Allowed resolutions
        bool allowedResolution[5];
    public:
        GeneralSettingsMenu(userSettings* settings);
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
        const float getVolumeLevel() override;
};

#endif