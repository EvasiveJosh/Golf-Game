#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include "match.h"
#include "raylib.h"
#include "ball.h"
#include "random"

class TerrainSquare{
    private:
        int height;
        int posX;
        int width;
        int id;
    public:
        TerrainSquare(int height, int posX, int width, int id);
        // void DrawSquare(TerrainSquare sq);
        int getHeight();
        int getPosX();
        int getId();
};


class Terrain{
    private:
        int difficulty;
    public:
        TerrainSquare DrawTerrain(int difficulty);
};

#endif
