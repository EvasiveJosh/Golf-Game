#include "singleplayerWinMenu.h"

SingleplayerWinMenu::SingleplayerWinMenu() : Menu()
{
    //Load mouse
    mouse = Mouse();
    //Load background texture
}

void SingleplayerWinMenu::draw()
{
    //Draw Textures
    //DrawTexture(textures.getTexture(0), 0, 0, WHITE);
    

}

void SingleplayerWinMenu::drawDebug()
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

GuiEvent SingleplayerWinMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            
        }
    }
    return Nothing;
}