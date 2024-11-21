#include "Flag.h"


Flag::Flag(){
    flagPosition = {0, 0};
    scale = 1.0;
    texture = LoadTexture("../resources/1.png");
}

Flag::Flag(float baseX, float baseY, float scale)
    : scale(scale) {
    flagPosition = { baseX - 72, baseY };
    texture = LoadTexture("../resources/1.png");
}


// Flag::~Flag() {
//     UnloadTexture(texture);
// }

void Flag::draw() const {
    float scaledX = sst::cxf(flagPosition.x);
    float scaledY = sst::cyf(flagPosition.y);
    
    float scaleX = (float)GetScreenWidth() / sst::baseX;
    float scaleY = (float)GetScreenHeight() / sst::baseY;
    
    Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dest = { 
        scaledX - sst::cxf(3), 
        scaledY - (texture.height * scaleY) + sst::cyf(16), 
        texture.width * scaleX, 
        texture.height * scaleY 
    };
    
    DrawTexturePro(texture, source, dest, {0, 0}, 0, WHITE);
}

Vector2 Flag::getPosition() const {
    return flagPosition;
}

void Flag::setPosition(int baseX, int baseY) {
    flagPosition = { (float)baseX, (float)baseY };
}
