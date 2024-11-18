#include "raylib.h"
#include <memory>
#include <string>

class GameMusic
{
    private:
        std::unique_ptr<Music> currentMusic;
    public:
        //Loads default starting music
        GameMusic();
        //Updates the music stream data
        void update();
        //Changes the music
        void change(const std::string& musicFilePath);
        //Properly closes music (should only be called in program.close)
        void close();
};