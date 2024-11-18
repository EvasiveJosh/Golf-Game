#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <stdexcept>

class userSettings {
    private:
        float volume;

    public:
        userSettings(float defaultVolume=1.0f);

        void setVolume(float vol);
        float getVolume();
};




#endif