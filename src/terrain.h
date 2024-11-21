#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include "match.h"
#include "raylib.h"
#include "ball.h"
#include "random"
#include "vector"
#include <cstdlib>
#include <ctime>  
#include "flag.h"


class TerrainSquare{
    private:
        int height;
        int posX;
        int width;
        int id;
    public:
        TerrainSquare(int height, int posX, int width, int id);
        // void DrawSquare(TerrainSquare sq);
        int getHeight() const;
        int getPosX() const;
        int getId() const;
        int getWidth() const;
};


class Terrain{
    private:
        int difficulty;
    public:
        std::vector<TerrainSquare> GenerateTerrain(int difficulty,Ball& golfball, const Flag& flag);
};

#endif
