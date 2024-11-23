#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "physicsObject.h"

class Rect : public PhysicsObject {
    private:
        int width;
        int height;
        CLITERAL(Color) fill_color;

    public:

        Rect(int w, int h, CLITERAL(Color) color=GREEN);

        void setWidth(int w);
        int getWidth();

        void setHeight(int h);
        int getHeight();

        void draw();
};




#endif