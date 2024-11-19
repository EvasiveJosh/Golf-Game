#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <stdexcept>

enum Resolution {
    _480P,
    _720P,
    _1080P,
    _1440P,
    _3840P
};


class userSettings {
    private:
        float volume;
        int screenX;
        int screenY;
        enum Resolution resolution;

    public:
        userSettings(
            float defaultVolume=0.0f, 
            int defaultScreenX=1280, 
            int defaultScreenY=720, 
            enum Resolution defaultResolution = _720P); // Set default volume to 0 because in repeat testing its very annoying
        // NOTE: Change default volume to 1.0f before release

        void setVolume(float vol);
        float getVolume();

        void setScreenX(int n);
        int getScreenX();

        void setScreenY(int n);
        int getScreenY();

        void setResolution(enum Resolution res);
        enum Resolution getResolution();

};




#endif