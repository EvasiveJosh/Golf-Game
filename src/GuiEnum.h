#ifndef GUIENUM_H
#define GUIENUM_H

enum MenuChoice
{
    StartingMenu,
    SingleplayerSettings,
    MultiplayerSettings,
    GeneralSettings
};

enum GuiEvent
{
    Nothing,
    Exit,
    OpenGeneralSettings,
    OpenStartingMenu,
    OpenMultiplayerMenu,
    OpenJoinMultiplayerMenu,
    screenSizeTo480p,
    screenSizeTo720p,
    screenSizeTo1080p,
    screenSizeTo1440p,
    screenSizeTo3840p,
    TryJoinMultiplayerGame,
    OpenSingleplayerGameSettingsMenu,
    StartSingleplayerGame,
    SetVolume,
    OpenSingleplayerWinMenu
};

#endif