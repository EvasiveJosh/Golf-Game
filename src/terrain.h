#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include "match.h"



class TerrainSquare{
    private:
        int height;
        int posX;
        int width;
        int id;
    public:
        void DrawSquare();
        int getHeight();
        int getPosX();
        int getId();
};


class Terrain{
    private:
        int difficulty;
    public:
        void DrawTerrain(int difficulty);

};

#endif
