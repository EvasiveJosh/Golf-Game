#ifndef SCREENSIZETRANSFER_H
#define SCREENSIZETRANSFER_H

/*

The following is a linear coordinate transfer function. Assume that everything on the screen has a base of 1280 x 720 (HD).
The transfer function t is used to properly scale up coordinates so that it fits on the screen.
This function should be applied to any x or y (or font) that is being used directly with a raylib function.
DO NOT use it in a class function unless otherwise specified.
*/

#include "raylib.h"

namespace sst
{
    inline const int baseX = 1280;
    inline const int baseY = 720;

    inline int cx(int x)
    {
        return (((float)GetScreenWidth())/baseX) * (float)x;
    }

    inline int cy(int y)
    {
        return (((float)GetScreenHeight())/baseY) * (float)y;
    }

    inline float cxf(float x)
    {
        return (((float)GetScreenWidth())/baseX) * x;
    }

    inline float cyf(float y)
    {
        return (((float)GetScreenHeight())/baseY) * y;
    }

    inline float cxfinv(float x)
    {
        return (baseX/((float)GetScreenWidth())) * x;
    }

    inline float cyfinv(float y)
    {
        return (baseY/((float)GetScreenHeight())) * y;
    }
}

#endif