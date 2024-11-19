#include "userSettings.h"

userSettings::userSettings(float defaultVolume, int defaultScreenX, int defaultScreenY, enum Resolution defaultResolution){
    this->volume = defaultVolume;
    this->screenX = defaultScreenX;
    this->screenY = defaultScreenY;
    this->resolution = defaultResolution;
}

float userSettings::getVolume(){
    return this->volume;
}

void userSettings::setVolume(float vol){
    if(vol < 0.0f || vol > 1.0f){
        throw std::runtime_error("Volume cannot be set outside of bounds 0-1");
    } else {
        this->volume = vol;
    }

}

int userSettings::getScreenX(){
    return this->screenX;
}

void userSettings::setScreenX(int n){
    this->screenX = n;
}

int userSettings::getScreenY(){
    return this->screenY;
}

void userSettings::setScreenY(int n){
    this->screenY = n;
}

void userSettings::setResolution(enum Resolution res){
    this->resolution = res;
}
enum Resolution userSettings::getResolution(){
    return this->resolution;
}