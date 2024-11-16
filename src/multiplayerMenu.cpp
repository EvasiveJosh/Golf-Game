#include "multiplayerMenu.h"

MultiplayerMenu::MultiplayerMenu() : Menu()
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
    text = "Host";
    addButton(text, font, centerTextX(text, font), centerTextY(text.c_str(), font) - (10 + font));
    text = "Join";
    addButton(text, font, centerTextX(text, font), centerTextY(text.c_str(), font) + (10 + font));
}

void MultiplayerMenu::draw()
{
    //Draw Textures
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);
    
    //Draw Text Options
    int font = 64;
    std::string text = "Multiplayer";
    DrawRectangleRec(surroundTextPad(text, font, centerTextX(text.c_str(), font), 10), DARKGREEN);
    DrawText(text.c_str(), sst::cx(centerTextX(text.c_str(), font)), sst::cy(10), sst::cx(font), BLACK);
    text = "Back";
    DrawText(text.c_str(), sst::cx(sst::baseX - MeasureText(text.c_str(), font) - 10), sst::cy(10), sst::cx(font), buttons[0].isHovered(mouse) ? RED : BLACK);

    font = 50;
    text = "Host";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(centerTextY(text.c_str(), font)) - sst::cx(10 + font), sst::cx(font), buttons[1].isHovered(mouse) ? RED : BLACK);
    text = "Join";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(centerTextY(text.c_str(), font)) + sst::cx(10 + font),  sst::cx(font), buttons[2].isHovered(mouse) ? RED : BLACK);
}

void MultiplayerMenu::drawDebug()
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

GuiEvent MultiplayerMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            case MMB_Back:
                return OpenStartingMenu;
            case MMB_Host:
                break;
            case MMB_Join:
                return OpenJoinMultiplayerMenu;
                break;
        }
    }
    return Nothing;
}