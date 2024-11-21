#include "lobby.h"

Lobby::Lobby(const std::string& username, const std::vector<int>& settings, int maxPlayers) 
    : Menu(), hostUsername(username), gameSettings(settings), playerLimit(maxPlayers)
{
    // Load mouse
    mouse = Mouse();
    // Load background texture
    textures.loadImage("resources", Background_M);
    textures.rescale(GetScreenWidth(), GetScreenHeight());
    textures.loadTexture();

    // Add initial host to connected players
    connectedPlayers.push_back(hostUsername);

    // Create buttons
    addButtons();
}

void Lobby::addButtons()
{
    int font = 64;
    std::string text = "Back";
    addButton(text, font, sst::baseX - MeasureText(text.c_str(), font) - 10, 10);

    text = "Start Game";
    addButton(text, font, centerTextX(text, font), sst::baseY - 100);
}

void Lobby::draw()
{
    // Draw background
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);

    // Draw title
    int font = 64;
    std::string text = "Lobby";
    DrawRectangleRec(surroundTextPad(text, font, centerTextX(text.c_str(), font), 10), DARKGREEN);
    DrawText(text.c_str(), sst::cx(centerTextX(text.c_str(), font)), sst::cy(10), sst::cx(font), BLACK);

    // Draw buttons
    text = "Back";
    DrawText(text.c_str(), sst::cx(sst::baseX - MeasureText(text.c_str(), font) - 10), 
            sst::cy(10), sst::cx(font), buttons[0].isHovered(mouse) ? RED : BLACK);

    text = "Start Game";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(sst::baseY - 100), 
            sst::cx(font), buttons[1].isHovered(mouse) ? RED : BLACK);

    // Draw lobby information on left side
    font = 55;
    int yPos = 120;
    
    // Draw host name
    text = "Host: " + hostUsername;
    DrawText(text.c_str(), sst::cx(20), sst::cy(yPos), sst::cx(font), BLACK);
    
    // Draw settings with text labels
    yPos += 80;
    std::string difficultyText;
    switch(gameSettings[0]) {
        case 0: difficultyText = "Easy"; break;
        case 1: difficultyText = "Medium"; break;
        case 2: difficultyText = "Hard"; break;
        default: difficultyText = "Unknown";
    }
    text = "Difficulty: " + difficultyText;
    DrawText(text.c_str(), sst::cx(20), sst::cy(yPos), sst::cx(font), BLACK);
    
    yPos += 80;
    std::string windText;
    switch(gameSettings[1]) {
        case 0: windText = "Off"; break;
        case 1: windText = "Light"; break;
        case 2: windText = "Heavy"; break;
        case 3: windText = "Unpredictable"; break;
        default: windText = "Unknown";
    }
    text = "Wind: " + windText;
    DrawText(text.c_str(), sst::cx(20), sst::cy(yPos), sst::cx(font), BLACK);
    
    yPos += 80;
    text = "Player Limit: " + std::to_string(playerLimit);
    DrawText(text.c_str(), sst::cx(20), sst::cy(yPos), sst::cx(font), BLACK);

    // Draw connected players on right side
    font = 55;
    text = "Connected Players:";
    int rightEdgeX = sst::baseX - 20;  // 20 pixels from right edge
    int textWidth = MeasureText(text.c_str(), font);
    DrawText(text.c_str(), sst::cx(rightEdgeX - textWidth), sst::cy(120), sst::cx(font), BLACK);
    
    // List connected players
    yPos = 200;
    for (const auto& player : connectedPlayers)
    {
        textWidth = MeasureText(player.c_str(), font);
        DrawText(player.c_str(), sst::cx(rightEdgeX - textWidth), sst::cy(yPos), sst::cx(font), BLACK);
        yPos += 60;
    }
}

GuiEvent Lobby::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch(buttonClicked())
        {
            case LMB_Back:
                return OpenHostMultiplayerMenu;
            case LMB_StartGame:
                // TODO: Implement multiplayer game start
                return Nothing;
        }
    }
    return Nothing;
}

void Lobby::drawDebug()
{
    DrawRectangleRec(mouse.mouseHitbox(), PURPLE);
    for (int i = 0; i < amountOfButtons(); i++)
    {
        DrawRectangleLinesEx(buttons[i].getBounds(), 5, PURPLE);
    }
    DrawText(TextFormat("Buttons[%i]", buttonClicked()), 0, 0, sst::cx(20), BLACK);
}
