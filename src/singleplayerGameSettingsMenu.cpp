#include "singleplayerGameSettingsMenu.h"

SingleplayerGameSettingsMenu::SingleplayerGameSettingsMenu() : Menu()
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
    text = "Start";
    addButton(text, font, sst::baseX - MeasureText(text.c_str(), font) - 150, 600);
    font = 50;
    text = "Easy";
    addButton(text, font, sst::baseX/5, 200);
    text = "Medium";
    addButton(text, font, sst::baseX/5 * 2 - 10, 200);
    text = "Hard";
    addButton(text, font, sst::baseX/5 * 3 + 20, 200);
    text = "Off";
    addButton(text, font, sst::baseX/7 - 20, 325);
    text = "Light";
    addButton(text, font, sst::baseX/7 * 2 - 50, 325);
    text = "Heavy";
    addButton(text, font, sst::baseX/7 * 3 - 40, 325);
    text = "Unpredictable";
    addButton(text, font, sst::baseX/7 * 4, 325);
    text = "On";
    addButton(text, font, sst::baseX/7 - 20, 500);
    text = "Off";
    addButton(text, font, sst::baseX/7 * 2 - 50, 500);

    //Default Settings
    difficulty = 1;
    wind = 0;
    endlessmode = 1;
    
}

void SingleplayerGameSettingsMenu::draw()
{
    //Draw Textures
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);
    
    //Draw Text Options
    int font = 64;
    std::string text = "Singleplayer Game Settings";
    DrawRectangleRec(surroundTextPad(text, font, centerTextX(text.c_str(), font), 10), DARKGREEN);
    DrawText(text.c_str(), sst::cx(centerTextX(text.c_str(), font)), sst::cy(10), sst::cx(font), BLACK);
    text = "Back";
    DrawText(text.c_str(), sst::cx(sst::baseX - MeasureText(text.c_str(), font) - 10), sst::cy(10), sst::cx(font), buttons[0].isHovered(mouse) ? RED : BLACK);
    text = "Start";
    DrawText(text.c_str(), sst::cx(sst::baseX - MeasureText(text.c_str(), font) - 150), sst::cy(600), sst::cx(font), buttons[1].isHovered(mouse) ? RED : BLACK);
    text = "Difficulty:";
    DrawText(text.c_str(), sst::cx(10), sst::cy(100), sst::cx(font), BLACK);
    text = "Wind:";
    DrawText(text.c_str(), sst::cx(10), sst::cy(250), sst::cx(font), BLACK);
    text = "Endless Mode:";
    DrawText(text.c_str(), sst::cx(10), sst::cy(400), sst::cx(font), BLACK);

    //Draw default configuration
    font = 50;
    text = "Easy";
    DrawText(text.c_str(), sst::cx(sst::baseX/5), sst::cy(200), sst::cx(font), buttons[2].isHovered(mouse) ? RED : BLACK);
    text = "Medium";
    DrawText(text.c_str(),sst::cx((sst::baseX/5) * 2 - 10), sst::cy(200), sst::cx(font), buttons[3].isHovered(mouse) ? RED : BLACK);
    text = "Hard";
    DrawText(text.c_str(), sst::cx((sst::baseX/5) * 3 + 20), sst::cy(200), sst::cx(font), buttons[4].isHovered(mouse) ? RED : BLACK);
    text = "Off";
    DrawText(text.c_str(), sst::cx(sst::baseX/7 - 20), sst::cy(325), sst::cx(font), buttons[5].isHovered(mouse) ? RED : BLACK);
    text = "Light";
    DrawText(text.c_str(),sst::cx((sst::baseX/7) * 2 - 50), sst::cy(325), sst::cx(font), buttons[6].isHovered(mouse) ? RED : BLACK);
    text = "Heavy";
    DrawText(text.c_str(),sst::cx((sst::baseX/7) * 3 - 40), sst::cy(325), sst::cx(font), buttons[7].isHovered(mouse) ? RED : BLACK);
    text = "Unpredictable";
    DrawText(text.c_str(),sst::cx((sst::baseX/7) * 4), sst::cy(325), sst::cx(font), buttons[8].isHovered(mouse) ? RED : BLACK);
    text = "On";
    DrawText(text.c_str(),sst::cx((sst::baseX/7) - 20), sst::cy(500), sst::cx(font), buttons[9].isHovered(mouse) ? RED : BLACK);
    text = "Off";
    DrawText(text.c_str(),sst::cx((sst::baseX/7) * 2 - 50), sst::cy(500), sst::cx(font), buttons[10].isHovered(mouse) ? RED : BLACK);

    //Now change the text to the color blue if it is selected (by drawing over it with the same text in the color blue)
    switch (difficulty)
    {
        case 0:
            text = "Easy";
            DrawText(text.c_str(), sst::cx(sst::baseX/5), sst::cy(200), sst::cx(font), BLUE);
            break;
        case 1:
            text = "Medium";
            DrawText(text.c_str(),sst::cx((sst::baseX/5) * 2 - 10), sst::cy(200), sst::cx(font), BLUE);
            break;
        case 2:
            text = "Hard";
            DrawText(text.c_str(), sst::cx((sst::baseX/5) * 3 + 20), sst::cy(200), sst::cx(font), BLUE);
            break;
    }
    switch (wind)
    {
        case 0:
            text = "Off";
            DrawText(text.c_str(), sst::cx(sst::baseX/7 - 20), sst::cy(325), sst::cx(font), BLUE);
            break;
        case 1:
            text = "Light";
            DrawText(text.c_str(),sst::cx((sst::baseX/7) * 2 - 50), sst::cy(325), sst::cx(font), BLUE);
            break;
        case 2:
            text = "Heavy";
            DrawText(text.c_str(),sst::cx((sst::baseX/7) * 3 - 40), sst::cy(325), sst::cx(font), BLUE);
            break;
        case 3:
            text = "Unpredictable";
            DrawText(text.c_str(),sst::cx((sst::baseX/7) * 4), sst::cy(325), sst::cx(font), BLUE);
            break;
    }
    switch (endlessmode)
    {
        case 0:
            text = "On";
            DrawText(text.c_str(),sst::cx((sst::baseX/7) - 20), sst::cy(500), sst::cx(font), BLUE);
            break;
        case 1:
            text = "Off";
            DrawText(text.c_str(),sst::cx((sst::baseX/7) * 2 - 50), sst::cy(500), sst::cx(font), BLUE);
            break;
    }

}

void SingleplayerGameSettingsMenu::drawDebug()
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

//State updates (based on buttons)
GuiEvent SingleplayerGameSettingsMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            case SGSMB_Back:
                return OpenStartingMenu;
                break;
            case SGSMB_Start:
                return StartSingleplayerGame;
                break;
            case SGSMB_D_Easy:
                difficulty = 0;
                break;
            case SGSMB_D_Medium:
                difficulty = 1;
                break;
            case SGSMB_D_Hard:
                difficulty = 2;
                break;
            case SGSMB_W_Off:
                wind = 0;
                break;
            case SGSMB_W_Light:
                wind = 1;
                break;
            case SGSMB_W_Heavy:
                wind = 2;
                break;
            case SGSMB_W_Unpredictable:
                wind = 3;
                break;
            case SGSMB_EM_Off:
                endlessmode = 0;
                break;
            case SGSMB_EM_On:
                endlessmode = 1;
                break;
        }
    }
    return Nothing;
}

std::vector<int> SingleplayerGameSettingsMenu::getInformation()
{
    return {difficulty, wind, endlessmode};
}
