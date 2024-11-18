#include "userSettings.h"

userSettings::userSettings(float defaultVolume){
    this->volume = defaultVolume;
}

float userSettings::getVolume(){
    return this->volume;
}

void userSettings::setVolume(float vol){
    if(vol < 0.0f or vol > 1.0f){
        throw std::runtime_error("Volume cannot be set outside of bounds 0-1");
    } else {
        this->volume = vol;
    }

}