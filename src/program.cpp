#include "program.h"
#include "startMenu.h"
#include "generalSettingsMenu.h"
#include "multiplayerMenu.h"
#include "joinMultiplayerMenu.h"
#include "singleplayerGameSettingsMenu.h"
#include "singleplayerWinMenu.h"
#include "singleplayerPauseMenu.h"
#include "hostMultiplayerMenu.h"
#include "lobby.h"
//Threads
#include <thread>
#include <chrono>
#include <atomic>


Program::Program() : currentMusic(), settings()
{
    SetConfigFlags(FLAG_VSYNC_HINT); // Vertical Sync (prevents screen tearing)
    InitWindow(sst::baseX, sst::baseY, "Game");

    SetTargetFPS(60);
    end = false;
    SetExitKey(KEY_NULL); //Removes escape as the exit key
    debug = false;
    //Initializes starting menu
    currentMenu = std::make_unique<StartMenu>();
    inSingleplayerGame = false;
    bool inMultiplayerGame = false;
    gameSettings = std::vector<int>();

}

void Program::close()
{
    currentMusic.close();
    CloseWindow(); //Closes the window
}

void Program::loop()
{
    std::atomic<bool> running(true);
    std::thread musicThread([&] {
        while(running.load()) 
        {
            currentMusic.update();
            std::this_thread::sleep_for(std::chrono::milliseconds(17)); // Approximation of 16.667 ms
        }
    });

    while (!end)
    {   
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) // For testing purposes
            end = true;
        
        if (IsKeyPressed(KEY_P))
            debug = !debug;
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Drawing updates
        if (inSingleplayerGame && currentMatch)
        {
            currentMatch->draw(); // Always draw the game
            if (debug)
                currentMatch->drawDebug();

            if (currentMenu) // If a menu is active, draw it on top
                currentMenu->draw();
        }
        else if (currentMenu)
        {
            currentMenu->draw();
            if (debug)
                currentMenu->drawDebug();
        }

        EndDrawing();

        // Logic updates
        if (inSingleplayerGame && currentMatch)
        {
            if (currentMenu) // If a menu is active, update its logic
                updateLogic(currentMenu->updateMenuLogic());
            else // If no menu, update game logic
                updateLogic(currentMatch->updateLogic());
        }
        else if (currentMenu)
        {
            updateLogic(currentMenu->updateMenuLogic());
        }
    }
    running.store(false);
    musicThread.join();
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
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(&this->settings);
            break;
        case OpenStartingMenu:
            if (inSingleplayerGame)
            {
                currentMatch = nullptr;
                inSingleplayerGame = false;
            }
            gameSettings.clear(); // Reset game settings when opening the starting menu
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
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(&this->settings); 
            break;
        case screenSizeTo720p:
            SetWindowSize(1280, 720);
            SetWindowPosition(GetMonitorWidth(0)/2 - 1280/2, GetMonitorHeight(0)/2 - 720/2); 
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(&this->settings); 
            break;
        case screenSizeTo1080p:
            SetWindowSize(1920, 1080);
            SetWindowPosition(GetMonitorWidth(0)/2 - 1920/2, GetMonitorHeight(0)/2 - 1080/2);
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(&this->settings); 
            break;
        case screenSizeTo1440p:
            SetWindowSize(2560, 1440);
            SetWindowPosition(GetMonitorWidth(0)/2 - 2560/2, GetMonitorHeight(0)/2 - 1440/2);
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(&this->settings); 
            break;
        case screenSizeTo3840p:
            SetWindowSize(3840, 2160);
            SetWindowPosition(GetMonitorWidth(0)/2 - 3840/2, GetMonitorHeight(0)/2 - 2160/2);
            this->currentMenu = std::make_unique<GeneralSettingsMenu>(&this->settings); 
            break;
        case TryJoinMultiplayerGame:
            username = this->currentMenu->getUserName(); //TODO, ensure no empty string can be returned...
            hostname = this->currentMenu->getHostName(); //TODO, ensure no empty string can be returned...
            inputIPAddress = this->currentMenu->getIpAddress(); //TODO, ensure no empty string can be returned...
            //what should the program do when the user tries to join a hosts lobby
            break;

        case OpenSingleplayerGameSettingsMenu:
            this->currentMenu = std::make_unique<SingleplayerGameSettingsMenu>();
            break;

        case StartSingleplayerGame:
            inSingleplayerGame = true;
            if (currentMenu && dynamic_cast<SingleplayerGameSettingsMenu*>(currentMenu.get())) {
                // If coming from settings menu, get new settings
                gameSettings = this->currentMenu->getInformation();
            }
            // Otherwise use existing gameSettings
            currentMatch = std::make_unique<SingleplayerMatch>(gameSettings);
            currentMenu = nullptr;
            break;
        
        case SetVolume:
            this->settings.setVolume(currentMenu->getVolumeLevel());
            currentMusic.setVolumeLevel(this->settings.getVolume());
            break;

        case OpenSingleplayerWinMenu:
            if (inSingleplayerGame)
            {
                int shotCount = dynamic_cast<SingleplayerMatch*>(currentMatch.get())->getShotCount();
                currentMatch = nullptr;
                inSingleplayerGame = false;
                this->currentMenu = std::make_unique<SingleplayerWinMenu>(shotCount);
            }
            break;
        
        case PauseGame:
            if (inSingleplayerGame && !currentMenu)
                currentMenu = std::make_unique<SingleplayerPauseMenu>();
            break;

        case ResumeGame:
            currentMenu = nullptr; // Remove the pause menu

            if (inSingleplayerGame)
                currentMatch->resume();
            break;
        
        case OpenHostMultiplayerMenu:
            this->currentMenu = std::make_unique<HostMultiplayerMenu>();
            break;

        case CreateLobby:
            if (currentMenu)
            {
                std::string username = currentMenu->getUserName();
                std::vector<int> settings = currentMenu->getInformation();
                int playerLimit = settings[2];
                this->currentMenu = std::make_unique<Lobby>(username, settings, playerLimit);
            }
            break;
    }
}
