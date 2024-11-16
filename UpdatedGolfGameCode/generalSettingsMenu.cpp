#include "generalSettingsMenu.h"

GeneralSettingsMenu::GeneralSettingsMenu() : Menu()
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
    //Determine which resolutions are not supported on main monitor


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
    text = "Resolution:";
    DrawText(text.c_str(), sst::cx(10), sst::cy(centerTextY(text.c_str(), font)) - sst::cy(font + 20), sst::cx(font), BLACK);
    font = 50;
    text = "480p";
    DrawText(text.c_str(), sst::cx(30+0*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[0] ? BLUE : (buttons[1].isHovered(mouse) ? RED : BLACK));
    text = "720p";
    DrawText(text.c_str(), sst::cx(30+1*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[1] ? BLUE : (buttons[2].isHovered(mouse) ? RED : BLACK));
    text = "1080p";
    DrawText(text.c_str(), sst::cx(30+2*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[2] ? BLUE : (buttons[3].isHovered(mouse) ? RED : BLACK));
    text = "1440p";
    DrawText(text.c_str(), sst::cx(30+3*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[3] ? BLUE : (buttons[4].isHovered(mouse) ? RED : BLACK));
    text = "3840p";
    DrawText(text.c_str(), sst::cx(30+4*214), sst::cy(centerTextY(text.c_str(), font)), sst::cx(font), currentResolution[4] ? BLUE : (buttons[5].isHovered(mouse) ? RED : BLACK)); 
    

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
                if (!currentResolution[0])
                    return screenSizeTo480p;
                break;
            case GSMB_720p:
                if (!currentResolution[1])
                    return screenSizeTo720p;
                break;
            case GSMB_1080p:
                if (!currentResolution[2])
                    return screenSizeTo1080p;
                break;
            case GSMB_1440p:
                if (!currentResolution[3])
                    return screenSizeTo1440p;
                break;
            case GSMB_3840p:
                if (!currentResolution[4])
                    return screenSizeTo3840p;
                break;
        }
    }
    return Nothing;
}