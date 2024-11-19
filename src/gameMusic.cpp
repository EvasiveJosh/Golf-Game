#include "gameMusic.h"

GameMusic::GameMusic()
{
    InitAudioDevice();
    currentMusic = std::make_unique<Music>(LoadMusicStream("resources/tempMusic.mp3"));
    PlayMusicStream(*currentMusic);
    volumeLevel = 0.0f; // Set default volume to 0 for repeat testing, remember to change before release
}

void GameMusic::update()
{
    if (currentMusic)
    {
        UpdateMusicStream(*currentMusic); //Update music stream with music data
        SetMusicVolume(*currentMusic, volumeLevel);
    }
}

void GameMusic::change(const std::string& musicFilePath)
{   
    //Unloads the current music stream
    if (currentMusic)
    {
        StopMusicStream(*currentMusic);
        currentMusic.reset();
    }

    //Load new music stream
    currentMusic = std::make_unique<Music>(LoadMusicStream(musicFilePath.c_str()));
    PlayMusicStream(*currentMusic);
}

void GameMusic::close()
{
    if (currentMusic)
        currentMusic.reset();
    CloseAudioDevice();
}

const float& GameMusic::getVolumeLevel()
{
    return volumeLevel;
}

void GameMusic::setVolumeLevel(const float& newVolumeLevel)
{
    volumeLevel = newVolumeLevel;
}