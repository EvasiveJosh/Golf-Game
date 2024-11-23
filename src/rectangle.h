#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "physicsObject.h"

class Rect : public PhysicsObject {
    private:
        int width = 0;
        int height = 0;
        CLITERAL(Color) fill_color;

    public:
        Rect();

        void setWidth(int w);
        int getWidth();

        void setHeight(int h);
        int getHeight();

        void setColor(CLITERAL(Color) color);
        CLITERAL(Color) getColor();
        void draw();
};




#endif