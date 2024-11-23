#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include "raylib.h"
#include "ball.h"
#include "random"
#include "vector"
#include <cstdlib>
#include <ctime>  
#include "flag.h"

class Ball;  // Forward declaration of Ball
class Flag;  // Forward declaration of Flag

class TerrainSquare {
private:
    int height;    // Height of the square
    int posX;      // X position
    int width;     // Width of the square
    int id;        // Unique identifier for the square
public:
    TerrainSquare(int height, int posX, int width, int id);

    // Getter methods
    int getHeight() const;
    int getPosX() const;
    int getWidth() const;
    int getId() const;

    // Draw method for the square
    void draw() const;
};


class Terrain{
    private:
        int difficulty;
    public:
        std::vector<TerrainSquare> GenerateTerrain(int difficulty,Ball& golfball, const Flag& flag);
};

#endif
