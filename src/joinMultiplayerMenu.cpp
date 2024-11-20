#include "joinMultiplayerMenu.h"

JoinMultiplayerMenu::JoinMultiplayerMenu() : Menu()
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
    text = "Your Username";
    usernameTextBox = { (float)centerTextX(text, font) - sst::baseX/4 - 5, (float)centerTextY(text.c_str(), font) - 150, 400, 70 };
    addButton(text, usernameTextBox); //Your username textbox
    text = "Host's Username";
    hostnameTextBox = { (float)centerTextX(text, font) + sst::baseX/4 + 11, (float)centerTextY(text.c_str(), font) - 150, 400, 70 };
    addButton(text, hostnameTextBox); //Hosts username textbox
    text = "IP Address";
    ipAddressTextBox = { (float)centerTextX(text, font) - 59 - 50, (float)centerTextY(text.c_str(), font) + (30 + font) - 50, 400 + 100, 70};
    addButton(text, ipAddressTextBox); //IP address textbox
    font = 64;
    text = "Join";
    addButton(text, font, centerTextX(text, font), centerTextY(text,font) + 150);

    usernameLetterCount = 0;
    hostnameLetterCount = 0;
    ipAddressLetterCount = 0;
    isModifyingUsername = false;
    isModifyingHostname = false;
    isModifyingIPAddress = false;
}

void JoinMultiplayerMenu::draw()
{
    //Draw Textures
    DrawTexture(textures.getTexture(0), 0, 0, WHITE);
    
    //Draw Text Options
    int font = 64;
    std::string text = "Join Multiplayer";
    DrawRectangleRec(surroundTextPad(text, font, centerTextX(text.c_str(), font), 10), DARKGREEN);
    DrawText(text.c_str(), sst::cx(centerTextX(text.c_str(), font)), sst::cy(10), sst::cx(font), BLACK);
    text = "Back";
    DrawText(text.c_str(), sst::cx(sst::baseX - MeasureText(text.c_str(), font) - 10), sst::cy(10), sst::cx(font), buttons[0].isHovered(mouse) ? RED : BLACK);
    font = 50;
    text = "Your Username";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font) - sst::baseX/4), sst::cy(centerTextY(text.c_str(), font) - (10 + font) - 150), sst::cx(font), BLACK);
    text = "Host's Username";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font) + sst::baseX/4), sst::cy(centerTextY(text.c_str(), font) - (10 + font) - 150),  sst::cx(font), BLACK);
    text = "IP Address";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(centerTextY(text.c_str(), font) + (50 + font) - 125),  sst::cx(font), BLACK);
    font = 64;
    text = "Join";
    DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(centerTextY(text,font) + 150), sst::cx(font), buttons[4].isHovered(mouse) ? RED : BLACK);

    //Draw textInput stuff
    int linethickness = 2;
    font = 50;
    DrawRectangle(sst::cx(usernameTextBox.x), sst::cy(usernameTextBox.y), sst::cx(usernameTextBox.width), sst::cy(usernameTextBox.height), WHITE);
    DrawRectangleLinesEx({sst::cxf(usernameTextBox.x), sst::cyf(usernameTextBox.y), sst::cxf(usernameTextBox.width), sst::cyf(usernameTextBox.height)}, sst::cx(linethickness), buttons[1].isHovered(mouse) ? RED : BLACK);
    DrawText(username, sst::cx((int)usernameTextBox.x + 20), sst::cy((int)usernameTextBox.y + 8), sst::cx(font), MAROON);

    DrawRectangle(sst::cx(hostnameTextBox.x), sst::cy(hostnameTextBox.y), sst::cx(hostnameTextBox.width), sst::cy(hostnameTextBox.height), WHITE);
    DrawRectangleLinesEx({sst::cxf(hostnameTextBox.x), sst::cyf(hostnameTextBox.y), sst::cxf(hostnameTextBox.width), sst::cyf(hostnameTextBox.height)}, sst::cx(linethickness), buttons[2].isHovered(mouse) ? RED : BLACK);
    DrawText(hostname, sst::cx((int)hostnameTextBox.x + 20), sst::cy((int)hostnameTextBox.y + 8), sst::cx(font), MAROON);

    DrawRectangleRec({sst::cxf(ipAddressTextBox.x), sst::cyf(ipAddressTextBox.y), sst::cxf(ipAddressTextBox.width), sst::cyf(ipAddressTextBox.height)}, WHITE);
    DrawRectangleLinesEx({sst::cxf(ipAddressTextBox.x), sst::cyf(ipAddressTextBox.y), sst::cxf(ipAddressTextBox.width), sst::cyf(ipAddressTextBox.height)}, sst::cx(linethickness), buttons[3].isHovered(mouse) ? RED : BLACK);
    DrawText(ipAddress, sst::cx((int)ipAddressTextBox.x + 20), sst::cy((int)ipAddressTextBox.y + 8), sst::cx(font), MAROON);

    if (isModifyingUsername || isModifyingHostname || isModifyingIPAddress)
    {
        text = "Must Finish Editing Before Continuing/Leaving";
        font = 20; 
        DrawText(text.c_str(), sst::cx(centerTextX(text, font)), sst::cy(centerTextY(text, font) - 275), sst::cx(font), MAROON);
    }
}   

void JoinMultiplayerMenu::drawDebug()
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
    DrawText(TextFormat("isModUser: %i", static_cast<int>(isModifyingUsername)), 0, sst::cy(40), sst::cx(20), BLACK);
    DrawText(TextFormat("isModHost: %i", static_cast<int>(isModifyingHostname)), 0, sst::cy(80), sst::cx(20), BLACK);
}

GuiEvent JoinMultiplayerMenu::updateMenuLogic()
{
    mouse.updateMousePosition();
    if (isModifyingUsername)
        modifyUsername();
    if (isModifyingHostname)
        modifyHostname();
    if (isModifyingIPAddress)
        modifyIPAddress();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (!isModifyingUsername && !isModifyingHostname && !isModifyingIPAddress)
        {
            switch(buttonClicked())
            {
                case JMMB_Back:
                    return OpenMultiplayerMenu;
                    break;
                case JMMB_MyUsername:
                    isModifyingUsername = true;
                    break;
                case JMMB_HostUsername:
                    isModifyingHostname = true;
                    break;
                case JMMB_IPAddress:
                    isModifyingIPAddress = true;
                    break;
                case JMMB_Join:
                    return TryJoinMultiplayerGame;
                    break;
            }
        } 
        else
        {
            switch(buttonClicked())
            {
                case JMMB_MyUsername:
                    isModifyingUsername = false;
                    break;
                case JMMB_HostUsername:
                    isModifyingHostname = false;
                    break;
                case JMMB_IPAddress:
                    isModifyingIPAddress = false;
                    break;
            }
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    return Nothing;
}

void JoinMultiplayerMenu::modifyUsername()
{
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    //Character setting
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
    //Remove character
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        usernameLetterCount--;
        if (usernameLetterCount < 0) usernameLetterCount = 0;
        username[usernameLetterCount] = '\0';
    }    
}

void JoinMultiplayerMenu::modifyHostname()
{
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    //Character setting
    int key = GetCharPressed();
    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (hostnameLetterCount < MAX_NAME_INPUT))
        {
            hostname[hostnameLetterCount] = (char)key;
            hostname[hostnameLetterCount+1] = '\0'; // Add null terminator at the end of the string
            hostnameLetterCount++;
        }
        key = GetCharPressed();  // Check next character in the queue  
    }
    //Remove character
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        hostnameLetterCount--;
        if (hostnameLetterCount < 0) hostnameLetterCount = 0;
        hostname[hostnameLetterCount] = '\0';
    }    
}

void JoinMultiplayerMenu::modifyIPAddress()
{
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    //Character setting
    int key = GetCharPressed();
    //Only 0,1,2,3,4,5,6,7,8,9,.,: are allowed
    while (key > 0)
    {
        if ((((key >= 48) && (key <= 58)) || (key == 46)) && (ipAddressLetterCount < MAX_IPADDRESS_INPUT))
        {
            ipAddress[ipAddressLetterCount] = (char)key;
            ipAddress[ipAddressLetterCount+1] = '\0'; // Add null terminator at the end of the string
            ipAddressLetterCount++;
        }
        key = GetCharPressed();  // Check next character in the queue  
    }
    //Remove character
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        ipAddressLetterCount--;
        if (ipAddressLetterCount < 0) 
            ipAddressLetterCount = 0;
        ipAddress[ipAddressLetterCount] = '\0';
    }       
}

std::string JoinMultiplayerMenu::getUserName()
{
    std::string ret;
    return ret.assign(username);
}
std::string JoinMultiplayerMenu::getHostName()
{
    std::string ret;
    return ret.assign(hostname);
}

std::string JoinMultiplayerMenu::getIpAddress()
{
    std::string ret;
    return ret.assign(ipAddress);
}