#include "singleplayerWinMenu.h"

SingleplayerWinMenu::SingleplayerWinMenu(int shotCount) : Menu(), shotCount(shotCount)
{
    // Load mouse
    mouse = Mouse();
    // Load background texture
    textures.loadImage("resources", Background_M);
    textures.rescale(GetScreenWidth(), GetScreenHeight());
    textures.loadTexture();

    // Create buttons
    addButtons();
}

void SingleplayerWinMenu::addButtons()
{
    int font = 64;
    int yStart = 160; // Starting y position for the first button
    int ySpacing = 104; // Vertical spacing between buttons

    std::string text = "Restart";
    int xPosition = centerTextX(text, font); // Center the button horizontally
    addButton(text, font, xPosition, yStart);

    text = "Exit to Main Menu";
    xPosition = centerTextX(text, font); // Re-center for the new text
    addButton(text, font, xPosition, yStart + ySpacing);
}

void SingleplayerWinMenu::draw()
{
    // Draw background texture
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);

    // Draw shot count
    std::string shotText = "Shots: " + std::to_string(shotCount);
    int shotTextX = centerTextX(shotText, 64);
    DrawText(shotText.c_str(), sst::cx(shotTextX), sst::cy(64), sst::cx(64), BLACK);

    // Draw buttons
    for (int i = 0; i < amountOfButtons(); i++)
    {
        std::string text = buttons[i].getLabel();
        int textX = centerTextX(text, 64); // Center the text horizontally
        int textY = 160 + i * 104; // Calculate the vertical position
        DrawText(text.c_str(), sst::cx(textX), sst::cy(textY), sst::cx(64), buttons[i].isHovered(mouse) ? RED : BLACK);
    }
}

GuiEvent SingleplayerWinMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            case SWMB_Restart:
                return StartSingleplayerGame;
            case SWMB_Exit:
                return OpenStartingMenu;
            default:
                return Nothing;
        }
    }
    return Nothing;
}

void SingleplayerWinMenu::drawDebug()
{
    // Draw mouse hitbox
    DrawRectangleRec(mouse.mouseHitbox(), PURPLE);
    // Draw button hitboxes
    for (int i = 0; i < amountOfButtons(); i++)
    {
        DrawRectangleLinesEx(buttons[i].getBounds(), 5, PURPLE);
    }
    // Show current selection
    DrawText(TextFormat("Buttons[%i]", buttonClicked()), 0, 0, sst::cx(20), BLACK);
}