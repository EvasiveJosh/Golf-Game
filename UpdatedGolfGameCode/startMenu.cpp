#include "startMenu.h"

StartMenu::StartMenu() : Menu()
{
    //Load mouse
    mouse = Mouse();
    //Load background texture
    textures.loadImage("resources", Background_M); //Get the background image
    textures.rescale(GetScreenWidth(), GetScreenHeight()); //Rescale background to fit windowSize
    textures.loadTexture(); //Load the image into a texture

    //Create buttons
    int font = 64;
    std::string text = "Singleplayer";
    addButton(text, font, centerTextX(text, font), 160 + font);
    text = "Multiplayer";
    addButton(text, font, centerTextX(text, font), 264  + font);
    text = "Settings";
    addButton(text, font, centerTextX(text, font), 368 + font);
    text = "Exit";
    addButton(text, font, centerTextX(text, font), 472 + font);
}

void StartMenu::draw()
{
    //Draw Textures
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);
    
    //Draw Text Options
    std::string text = "Golf Game";
    int font = 80;
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(64), sst::cx(font), DARKGREEN);
    font = 64;
    text = "Singleplayer";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(160 + font), sst::cx(font), buttons[0].isHovered(mouse) ? RED : BLACK);
    text = "Multiplayer";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(264  + font),  sst::cx(font), buttons[1].isHovered(mouse) ? RED : BLACK);
    text = "Settings";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(368 + font),  sst::cx(font), buttons[2].isHovered(mouse) ? RED : BLACK);
    text = "Exit";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(472 + font),  sst::cx(font), buttons[3].isHovered(mouse) ? RED : BLACK);
}

void StartMenu::drawDebug()
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

GuiEvent StartMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            case SMB_Singleplayer:
                return OpenSingleplayerGameSettingsMenu;
                break;
            case SMB_Multiplayer:
                return OpenMultiplayerMenu;
                break;
            case SMB_Settings:
                return OpenGeneralSettings;
                break;
            case SMB_Exit:
                return Exit;
                break;
        }
    }
    return Nothing;
}