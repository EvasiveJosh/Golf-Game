#include "program.h"


Program::Program() : currentMusic()
{
    InitWindow(sst::baseX, sst::baseY, "Game");

    SetTargetFPS(60);
    end = false;
    SetExitKey(KEY_NULL); //Removes escape as the exit key
    debug = false;
    //Initializes starting menu
    currentMenu = std::make_unique<StartMenu>();
    inSingleplayerGame = false;
    bool inMultiplayerGame = false;
}

void Program::close()
{
    currentMusic.close();
    CloseWindow(); //Closes the window
}

void Program::loop()
{
    while(!end)
    {
        currentMusic.update();
        
        if (IsKeyPressed(KEY_ESCAPE)) //For testing purposes
            end = true;
        
        if (IsKeyPressed(KEY_P))
            debug = !debug;
        
        BeginDrawing();
            ClearBackground(RAYWHITE);


            if (!inSingleplayerGame && !inMultiplayerGame)
            {
                currentMenu->draw();
                if (debug)
                    currentMenu->drawDebug();
            }
            if (inSingleplayerGame)
            {
                currentMatch->draw();
                if (debug)
                    currentMatch->drawDebug();
            }

        EndDrawing();
        if (!inSingleplayerGame && !inMultiplayerGame)
            updateLogic(currentMenu->updateMenuLogic()); //Compute new state for menu
        if (inSingleplayerGame)
            updateLogic(currentMatch->updateLogic()); //Compute new state for sp match
    }
}

void Program::updateLogic(GuiEvent state)
{
    switch(state)
    {
        case Nothing:
            break;
        case Exit:
            end = true;
            break;
        case OpenGeneralSettings:
            this->currentMenu = std::make_unique<GeneralSettingsMenu>();
            break;
        case OpenStartingMenu:
            if (inSingleplayerGame)
            {
                currentMatch = nullptr;
                inSingleplayerGame = false;
            }
            this->currentMenu = std::make_unique<StartMenu>();
            break;
        case OpenMultiplayerMenu:
            this->currentMenu = std::make_unique<MultiplayerMenu>();
            break;
        case OpenJoinMultiplayerMenu:
            this->currentMenu = std::make_unique<JoinMultiplayerMenu>();
            break;
        case screenSizeTo480p:
            SetWindowSize(854, 480);
            SetWindowPosition(GetMonitorWidth(0)/2 - 854/2, GetMonitorHeight(0)/2 - 480/2); 
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(); 
            break;
        case screenSizeTo720p:
            SetWindowSize(1280, 720);
            SetWindowPosition(GetMonitorWidth(0)/2 - 1280/2, GetMonitorHeight(0)/2 - 720/2); 
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(); 
            break;
        case screenSizeTo1080p:
            SetWindowSize(1920, 1080);
            SetWindowPosition(GetMonitorWidth(0)/2 - 1920/2, GetMonitorHeight(0)/2 - 1080/2);
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(); 
            break;
        case screenSizeTo1440p:
            
            break;
        case screenSizeTo3840p:
            
            break;
        case TryJoinMultiplayerGame:
            username = this->currentMenu->getUserName(); //TODO, ensure no empty string can be returned...
            hostname = this->currentMenu->getHostName(); //TODO, ensure no empty string can be returned...
            //what should the program do when the user tries to join a hosts lobby
            break;

        case OpenSingleplayerGameSettingsMenu:
            this->currentMenu = std::make_unique<SingleplayerGameSettingsMenu>();
            break;

        case StartSingleplayerGame:
            std::vector<int> info = this->currentMenu->getInformation();
            inSingleplayerGame = true;
            currentMenu = nullptr;
            currentMatch = std::make_unique<SingleplayerMatch>(info[0], info[1], !info[2]);
            break;
        
    }
}
