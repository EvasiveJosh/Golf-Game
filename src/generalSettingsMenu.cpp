#include "generalSettingsMenu.h"

GeneralSettingsMenu::GeneralSettingsMenu(userSettings* settings) : Menu()
{
    //Load mouse
    mouse = Mouse();
    //Load background texture
    textures.loadImage("resources", Background_M); //Get the background image
    textures.rescale(GetScreenWidth(), GetScreenHeight()); //Rescale background to fit windowSize
    textures.loadTexture(); //Load the image into a texture

    //Create buttons
    int font = 64;
    std::string text = "Back";
    addButton(text, font, sst::baseX - MeasureText(text.c_str(), font) - 10, 10);
    font = 50;
    text = "480p";
    addButton(text.c_str(), font, 30+0*214, centerTextY(text.c_str(), font));
    text = "720p";
    addButton(text.c_str(), font, 30+1*214, centerTextY(text.c_str(), font));
    text = "1080p";
    addButton(text.c_str(), font, 30+2*214, centerTextY(text.c_str(), font));
    text = "1440p";
    addButton(text.c_str(), font, 30+3*214, centerTextY(text.c_str(), font));
    text = "3840p"; 
    addButton(text.c_str(), font, 30+4*214, centerTextY(text.c_str(), font));

    //Detect current screen size
    for (int i = 0; i < 5; i++)
        currentResolution[i] = false;
    switch(GetScreenHeight())
    {
        case 480:
            currentResolution[0] = true;
            break;
        case 720:
            currentResolution[1] = true;
            break;
        case 1080:
            currentResolution[2] = true;
            break;
        case 1440:
            currentResolution[3] = true;
            break;
        case 2160:
            currentResolution[4] = true;
            break;
    }
    //Determine which resolutions are not supported on main monitor (assume 720p and 480p are supported)
    for (int i = 0; i < 5; i++)
        allowedResolution[i] = true;

    int monitorHeightCheck = GetMonitorHeight(0);
    if (monitorHeightCheck < 1080)
        allowedResolution[2] = false;
    if (monitorHeightCheck < 1440)
        allowedResolution[3] = false;
    if (monitorHeightCheck < 2160)
        allowedResolution[4] = false;

    //Default volume level
    volumeLevel = settings->getVolume();

}

void GeneralSettingsMenu::draw()
{
    //Draw Background Texture
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);

    int font = 64;
    std::string text = "General Settings";
    DrawRectangleRec(surroundTextPad(text, font, centerTextX(text.c_str(), font), 10), DARKGREEN);
    DrawText(text.c_str(), sst::cx(centerTextX(text.c_str(), font)), sst::cy(10), sst::cx(font), BLACK);
    text = "Back";
    DrawText(text.c_str(), sst::cx(sst::baseX - MeasureText(text.c_str(), font) - 10), sst::cy(10), sst::cx(font), buttons[0].isHovered(mouse) ? RED : BLACK);
    
    //Volume Slider
    text = "Volume:";
    DrawText(text.c_str(), sst::cx(10), sst::cy(centerTextY(text.c_str(), font)) - sst::cy(font + 200), sst::cx(font), BLACK);
    float temp = volumeLevel;
    GuiSlider((Rectangle){sst::cxf(100), sst::cyf(centerTextY(text.c_str(), font)) - sst::cyf(font + 100), sst::cxf(1000), sst::cyf(40)}, "", "", &temp, 0.0f, 1.0f);
    volumeLevel = temp;

    //Resolution
    text = "Resolution:";
    DrawText(text.c_str(), sst::cx(10), sst::cy(centerTextY(text.c_str(), font)) - sst::cy(font + 20), sst::cx(font), BLACK);
    font = 50;
    text = "480p";
    DrawText(text.c_str(), sst::cx(30+0*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[0] ? BLUE : (allowedResolution[0] ? (buttons[1].isHovered(mouse) ? RED : BLACK) : BLACK));
    text = "720p";
    DrawText(text.c_str(), sst::cx(30+1*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[1] ? BLUE : (allowedResolution[1] ? (buttons[2].isHovered(mouse) ? RED : BLACK) : BLACK));
    text = "1080p";
    DrawText(text.c_str(), sst::cx(30+2*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[2] ? BLUE : (allowedResolution[2] ? (buttons[3].isHovered(mouse) ? RED : BLACK) : BLACK));
    text = "1440p";
    DrawText(text.c_str(), sst::cx(30+3*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[3] ? BLUE : (allowedResolution[3] ? (buttons[4].isHovered(mouse) ? RED : BLACK) : BLACK));
    text = "3840p";
    DrawText(text.c_str(), sst::cx(30+4*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[4] ? BLUE : (allowedResolution[4] ? (buttons[5].isHovered(mouse) ? RED : BLACK) : BLACK)); 

    //Draw indication that resolution is not allowed
    text = "Main Monitor too small";
    font = 15;
    for(int i = 0; i < 5; i++)
    {
        if (!allowedResolution[i])
            DrawText(text.c_str(), sst::cx(20+i*214), sst::cy(centerTextY(text.c_str(), font) + 55), sst::cx(font), RED); 
    }
    

}

void GeneralSettingsMenu::drawDebug()
{
    //Draw mouse hitbox
    DrawRectangleRec(mouse.mouseHitbox(), PURPLE);
    //Draw button hitboxes
    for (int i = 0; i < amountOfButtons(); i++)
    {
        DrawRectangleLinesEx(buttons[i].getBounds(), 5, PURPLE);
    }
    //Show current selection
    DrawText(TextFormat("Buttons[%i]", buttonClicked()), 0, 0, sst::cx(20), BLACK);
    //Show allowedResolution
    DrawText(TextFormat("MonitorHeight: %i", GetMonitorHeight(0)), sst::cx(50), sst::cy(sst::baseY - 300), sst::cx(20), BLACK);
    for (int i = 0; i < 5; i++)
    {
        DrawText(TextFormat("allowedResolution[%i]: %i", i, static_cast<int>(allowedResolution[i])), sst::cx(50), sst::cy((50 + 30 * i) + sst::baseY - 300), sst::cx(20),BLACK);
    }
    //Show currentResolution
    for (int i = 0; i < 5; i++)
    {
        DrawText(TextFormat("currentResolution[%i]: %i", i, static_cast<int>(currentResolution[i])), sst::cx(sst::baseX - 300), sst::cy((50 + 30 * i) + sst::baseY - 300), sst::cx(20),BLACK);
    }
}

GuiEvent GeneralSettingsMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            case GSMB_Back:
                return OpenStartingMenu;
                break;
            case GSMB_480p:
                if (!currentResolution[0] && allowedResolution[0])
                    return screenSizeTo480p;
                break;
            case GSMB_720p:
                if (!currentResolution[1] && allowedResolution[1])
                    return screenSizeTo720p;
                break;
            case GSMB_1080p:
                if (!currentResolution[2] && allowedResolution[2])
                    return screenSizeTo1080p;
                break;
            case GSMB_1440p:
                if (!currentResolution[3] && allowedResolution[3])
                    return screenSizeTo1440p;
                break;
            case GSMB_3840p:
                if (!currentResolution[4] && allowedResolution[4])
                    return screenSizeTo3840p;
                break;
        }
    }
    return SetVolume;
}

const float GeneralSettingsMenu::getVolumeLevel()
{
    return volumeLevel;
}