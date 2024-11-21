#include "hostMultiplayerMenu.h"

HostMultiplayerMenu::HostMultiplayerMenu() : Menu()
{
    // Load mouse
    mouse = Mouse();
    // Load background texture
    textures.loadImage("resources", Background_M);
    textures.rescale(GetScreenWidth(), GetScreenHeight());
    textures.loadTexture();

    // Create buttons
    addButtons();

    usernameLetterCount = 0;
    isModifyingUsername = false;

    // Default Settings
    difficulty = 1;
    wind = 1;
    playerLimit = 4;
}

void HostMultiplayerMenu::addButtons()
{
    int font = 64;
    std::string text = "Back";
    addButton(text, font, sst::baseX - MeasureText(text.c_str(), font) - 10, 10);  // Index 0

    font = 50;
    text = "Your Username";
    usernameTextBox = { 20.0f, 150.0f, 400.0f, 70.0f };
    addButton(text, usernameTextBox);

    // Add game settings buttons
    int yPosition = 270;
    text = "Easy";
    addButton(text, font, 300, yPosition); // Index 2
    text = "Medium";
    addButton(text, font, 450, yPosition); // Index 3
    text = "Hard";
    addButton(text, font, 650, yPosition); // Index 4
    yPosition += 100;
    text = "Off";
    addButton(text, font, 170, yPosition); // Index 5
    text = "Light";
    addButton(text, font, 300, yPosition); // Index 6
    text = "Heavy";
    addButton(text, font, 450, yPosition); // Index 7
    text = "Unpredictable";
    addButton(text, font, 640, yPosition); // Index 8
    yPosition += 100;

    // Player Limit Slider
    text = "Player Limit";
    addButton(text, font, 20, yPosition); // Index 9

    // Create Room Button
    font = 64;
    text = "Create Room";
    addButton(text, font, 620, yPosition+64+8);
}

void HostMultiplayerMenu::draw()
{
    // Draw Textures
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);

    // Draw Title
    int font = 64;
    std::string text = "Host Multiplayer";
    DrawRectangleRec(surroundTextPad(text, font, centerTextX(text.c_str(), font), 10), DARKGREEN);
    DrawText(text.c_str(), sst::cx(centerTextX(text.c_str(), font)), sst::cy(10), sst::cx(font), BLACK);
    
    // Draw Back Button
    text = "Back";
    DrawText(text.c_str(), sst::cx(sst::baseX - MeasureText(text.c_str(), font) - 10), sst::cy(10), sst::cx(font), buttons[0].isHovered(mouse) ? RED : BLACK);

    // Draw Username Input Box
    font = 50;
    text = "Your Username";
    DrawText(text.c_str(), sst::cx(20), sst::cy(100), sst::cx(font), BLACK);
    
    // Draw textInput with red highlight when hovered
    int linethickness = 2;
    DrawRectangle(sst::cx(20), sst::cy(150), sst::cx(400), sst::cy(70), WHITE);
    DrawRectangleLinesEx({sst::cxf(20), sst::cyf(150), sst::cxf(400), sst::cyf(70)}, 
                        sst::cx(linethickness), 
                        buttons[1].isHovered(mouse) ? RED : BLACK);
    DrawText(username, sst::cx(40), sst::cy(158), sst::cx(font), MAROON);

    // Draw error message if username is empty
    if (usernameLetterCount == 0) {
        font = 20;
        text = "Username must be at least 1 character";
        DrawText(text.c_str(), sst::cx(20), sst::cy(230), sst::cx(font), RED);
    }

    // Draw warning text when editing
    if (isModifyingUsername)
    {
        text = "Must Finish Editing Before Continuing/Leaving";
        font = 20;
        DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(centerTextY(text, font) - 275), sst::cx(font), MAROON);
    }

    font = 50;
    // Draw Game Settings
    int yPosition = 270;
    text = "Difficulty:";
    DrawText(text.c_str(), sst::cx(20), sst::cy(yPosition), sst::cx(font), BLACK);
    DrawText("Easy", sst::cx(300), sst::cy(yPosition), sst::cx(font), buttons[2].isHovered(mouse) ? RED : BLACK);
    DrawText("Medium", sst::cx(450), sst::cy(yPosition), sst::cx(font), buttons[3].isHovered(mouse) ? RED : BLACK);
    DrawText("Hard", sst::cx(650), sst::cy(yPosition), sst::cx(font), buttons[4].isHovered(mouse) ? RED : BLACK);

    // Highlight selected difficulty
    switch (difficulty)
    {
        case 0:
            DrawText("Easy", sst::cx(300), sst::cy(yPosition), sst::cx(font), BLUE);
            break;
        case 1:
            DrawText("Medium", sst::cx(450), sst::cy(yPosition), sst::cx(font), BLUE);
            break;
        case 2:
            DrawText("Hard", sst::cx(650), sst::cy(yPosition), sst::cx(font), BLUE);
            break;
    }

    yPosition += 100;
    text = "Wind:";
    DrawText(text.c_str(), sst::cx(20), sst::cy(yPosition), sst::cx(font), BLACK);
    DrawText("Off", sst::cx(170), sst::cy(yPosition), sst::cx(font), buttons[5].isHovered(mouse) ? RED : BLACK);
    DrawText("Light", sst::cx(300), sst::cy(yPosition), sst::cx(font), buttons[6].isHovered(mouse) ? RED : BLACK);
    DrawText("Heavy", sst::cx(450), sst::cy(yPosition), sst::cx(font), buttons[7].isHovered(mouse) ? RED : BLACK);
    DrawText("Unpredictable", sst::cx(640), sst::cy(yPosition), sst::cx(font), buttons[8].isHovered(mouse) ? RED : BLACK);

    // Highlight selected wind
    switch (wind)
    {
        case 0:
            DrawText("Off", sst::cx(170), sst::cy(yPosition), sst::cx(font), BLUE);
            break;
        case 1:
            DrawText("Light", sst::cx(300), sst::cy(yPosition), sst::cx(font), BLUE);
            break;
        case 2:
            DrawText("Heavy", sst::cx(450), sst::cy(yPosition), sst::cx(font), BLUE);
            break;
        case 3:
            DrawText("Unpredictable", sst::cx(640), sst::cy(yPosition), sst::cx(font), BLUE);
            break;
    }

    // Draw Player Limit Slider
    yPosition += 100;
    text = "Player Limit:";
    DrawText(text.c_str(), sst::cx(20), sst::cy(yPosition), sst::cx(font), BLACK);

    // Define the range for player limit
    int minPlayers = 1;
    int maxPlayers = 10;

    // Create a temporary variable to hold the slider value
    float tempPlayerLimit = static_cast<float>(playerLimit);

    // Draw the slider
    GuiSlider(
        (Rectangle){sst::cxf(20), sst::cyf(yPosition+64), sst::cxf(400), sst::cyf(64)},
        "", "", &tempPlayerLimit, static_cast<float>(minPlayers), static_cast<float>(maxPlayers)
    );

    // Update the playerLimit with the new value from the slider - casted to int to avoid float precision issues
    playerLimit = static_cast<int>(tempPlayerLimit);

    // Draw the current player limit value next to the slider
    std::string playerLimitText = std::to_string(playerLimit);
    DrawText(playerLimitText.c_str(), sst::cx(450), sst::cy(yPosition+64+8), sst::cx(font), BLACK);

    // Draw Create Room Button
    text = "Create Room";
    DrawText(text.c_str(), sst::cx(620), sst::cy(yPosition+64+8), sst::cx(font), buttons[10].isHovered(mouse) ? RED : BLACK);
}

GuiEvent HostMultiplayerMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (isModifyingUsername)
        modifyUsername();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (!isModifyingUsername)
        {
            switch(buttonClicked())
            {
                case HMMB_Back:
                    return OpenMultiplayerMenu;
                case HMMB_SetUsername:
                    isModifyingUsername = true;
                    break;
                case HMMB_D_Easy:
                    difficulty = 0;
                    break;
                case HMMB_D_Medium:
                    difficulty = 1;
                    break;
                case HMMB_D_Hard:
                    difficulty = 2;
                    break;
                case HMMB_W_Off:
                    wind = 0;
                    break;
                case HMMB_W_Light:
                    wind = 1;
                    break;
                case HMMB_W_Heavy:
                    wind = 2;
                    break;
                case HMMB_W_Unpredictable:
                    wind = 3;
                    break;
                case HMMB_PL_Limit:
                    // Placeholder
                    break;
                case HMMB_CreateRoom:
                    // Level settings and username from here are passed to the lobby
                    // In the lobby, the joinable room will be created according to multiplayer logic
                    // Only allow creating room if username is not empty
                    if (usernameLetterCount > 0) {
                        return CreateLobby;
                    }
                    break;
            }
        }
        else
        {
            if (buttonClicked() == HMMB_SetUsername)
            {
                isModifyingUsername = false;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
    }
    return Nothing;
}

void HostMultiplayerMenu::modifyUsername()
{
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    // Character setting
    int key = GetCharPressed();
    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (usernameLetterCount < MAX_NAME_INPUT))
        {
            username[usernameLetterCount] = (char)key;
            username[usernameLetterCount+1] = '\0'; // Add null terminator at the end of the string
            usernameLetterCount++;
        }
        key = GetCharPressed();  // Check next character in the queue  
    }
    // Remove character
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        usernameLetterCount--;
        if (usernameLetterCount < 0) usernameLetterCount = 0;
        username[usernameLetterCount] = '\0';
    }    
}

std::string HostMultiplayerMenu::getUserName()
{
    std::string ret;
    return ret.assign(username);
}

void HostMultiplayerMenu::drawDebug()
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

std::vector<int> HostMultiplayerMenu::getInformation()
{
    return {difficulty, wind, playerLimit};
}
