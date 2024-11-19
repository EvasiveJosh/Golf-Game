#include "singleplayerPauseMenu.h"

SingleplayerPauseMenu::SingleplayerPauseMenu() : Menu()
{
    // Load mouse
    mouse = Mouse();
    // Optionally load a background texture
    // textures.loadImage("resources", Background_M);
    // textures.rescale(GetScreenWidth(), GetScreenHeight());
    // textures.loadTexture();

    // Create buttons
    addButtons();
}

void SingleplayerPauseMenu::addButtons()
{
    int font = 64;
    int yStart = 160; // Starting y position for the first button
    int ySpacing = 104; // Vertical spacing between buttons

    std::string text = "Resume";
    int xPosition = centerTextX(text, font); // Center the button horizontally
    addButton(text, font, xPosition, yStart);

    text = "Return to Start Menu";
    xPosition = centerTextX(text, font); // Re-center for the new text
    addButton(text, font, xPosition, yStart + ySpacing);
}

void SingleplayerPauseMenu::draw()
{
    // Draw a semi-transparent overlay
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));

    // Draw buttons
    for (int i = 0; i < amountOfButtons(); i++)
    {
        std::string text = buttons[i].getLabel();
        int textX = centerTextX(text, 64); // Center the text horizontally
        int textY = 160 + i * 104; // Calculate the vertical position
        DrawText(text.c_str(), sst::cx(textX), sst::cy(textY), sst::cx(64), buttons[i].isHovered(mouse) ? RED : BLACK);
    }
}

GuiEvent SingleplayerPauseMenu::updateMenuLogic()
{
    mouse.updateMousePosition(); // Update mouse position
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            case SPMB_Resume:
                return ResumeGame;
            case SPMB_ReturnToStart:
                return OpenStartingMenu;
            default:
                return Nothing;
        }
    }
    return Nothing;
}

void SingleplayerPauseMenu::drawDebug()
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

