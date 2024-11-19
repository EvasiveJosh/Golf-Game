#ifndef FLAG_H
#define FLAG_H

#include "raylib.h"
#include "math.h"
#include "screenSizeTransfer.h"

class Flag{
    private:
        Vector2 flagPosition;

    public:
        Flag(int x, int y);
};


#endif