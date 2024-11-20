#include "Flag.h"


Flag::Flag(){
    flagPosition = {sst::cxf(0),sst::cyf(0)};
    scale = 1.0;
    texture = LoadTexture("../resources/1.png");
}

Flag::Flag(int baseX, int baseY, float scale)
    : scale(scale) {
    flagPosition = { sst::cxf(baseX), sst::cyf(baseY) };
    texture = LoadTexture("../resources/1.png");
}


// Flag::~Flag() {
//     UnloadTexture(texture);
// }

void Flag::draw() const {
   DrawTexture(texture, flagPosition.x, sst::cy(flagPosition.y - GRASS_HEIGHT - 189), WHITE);
}

Vector2 Flag::getPosition() const {
    return{flagPosition.x,flagPosition.y};
}

void Flag::setPosition(int baseX, int baseY) {
    flagPosition = { sst::cxf(baseX), sst::cyf(baseY) };
}
