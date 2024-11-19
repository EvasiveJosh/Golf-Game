#ifndef PROGRAM_H
#define PROGRAM_H

//Required includes for Gui
#include <memory>
#include "raylib.h"
#include "screenSizeTransfer.h"
#include "GuiEnum.h"
#include "mouse.h"
#include "menu.h"
#include "startMenu.h"
#include "generalSettingsMenu.h"
#include "multiplayerMenu.h"
#include "joinMultiplayerMenu.h"
#include "singleplayerGameSettingsMenu.h"
#include "singleplayerWinMenu.h"
#include "singleplayerPauseMenu.h"
//Actual Game windows
#include "match.h"
#include "singleplayerMatch.h"
//Other includes
#include "gameMusic.h"
#include "userSettings.h"



class Program
{
    private:
        std::string username;
        std::string hostname;
        //Gui Stuff
        bool end;
        bool debug;
        std::unique_ptr<Menu> currentMenu;       
        bool inSingleplayerGame;
        bool inMultiplayerGame;
        std::unique_ptr<Match> currentMatch;
        GameMusic currentMusic;
        userSettings settings;
        
    public:
        Program();
        void loop();
        void close();
    private:
        void updateLogic(GuiEvent state);
};

#endif