#ifndef FLAG_H
#define FLAG_H

#include "raylib.h"
#include "screenSizeTransfer.h"
#include "textureClass.h"
#include "ball.h"

class Flag {
private:
    Vector2 flagPosition; //flag coords
    Texture2D texture;    //flag texture
    float scale;          //scale

public:
    Flag();
    Flag(float baseX, float baseY, float scale = 1.0f);
    // ~Flag();

    void draw() const;    //draw the flag
    Vector2 getPosition() const; //get flag position
    void setPosition(int baseX, int baseY); //set flag position
};

#endif
