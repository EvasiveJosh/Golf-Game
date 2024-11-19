#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <stdexcept>

class userSettings {
    private:
        float volume;

    public:
        userSettings(float defaultVolume=0.0f); // Set default volume to 0 because in repeat testing its very annoying
        // NOTE: Change default volume to 1.0f before release

        void setVolume(float vol);
        float getVolume();
};




#endif