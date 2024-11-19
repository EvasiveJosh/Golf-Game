#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <stdexcept>

class userSettings {
    private:
        float volume;

    public:
        userSettings(
            // NOTE: Change default volume to 0.5f before release
            float defaultVolume=0.0f, // Set default volume to 0 because in repeat testing its very annoying
            int defaultScreenX=1280, 
            int defaultScreenY=720, 
            enum Resolution defaultResolution = _720P); 
        

        void setVolume(float vol);
        float getVolume();
};




#endif