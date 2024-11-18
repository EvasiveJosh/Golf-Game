#include "gameMusic.h"

GameMusic::GameMusic()
{
    InitAudioDevice();
    currentMusic = std::make_unique<Music>(LoadMusicStream("resources/tempMusic.mp3"));
    PlayMusicStream(*currentMusic);
}

void GameMusic::update()
{
    UpdateMusicStream(*currentMusic); //Update music stream with music data
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