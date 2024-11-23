#include <iostream>
#include "terrain.h"

using namespace std;

TerrainSquare::TerrainSquare(int h, int X, int w, int i) 
    : height(h), posX(X), width(w), id(i) {}

// Getter methods
int TerrainSquare::getHeight() const { return height; }
int TerrainSquare::getPosX() const { return posX; }
int TerrainSquare::getWidth() const { return width; }
int TerrainSquare::getId() const { return id; }

/*

*/
vector<TerrainSquare> Terrain::GenerateTerrain(int difficulty, Ball& golfball, const Flag& flag){
    Vector2 ballPosVec = golfball.getBallPosition();
    Vector2 flagposVec = flag.getPosition();
    int levelSize = 0;

    switch (difficulty) {
        case 0: levelSize = 8; break;  // Easy
        case 1: levelSize = 15; break;  // Medium
        default: levelSize = 20; break; // Hard
    }

    //get the width between the ball and flag
    int totalWidth = flagposVec.x - (ballPosVec.x + 50);
    
    //get the width that each segment can be and fit in the level size
    int segmentWidth = totalWidth / levelSize;

    //starting x position for segment
    int x = ballPosVec.x + 50;
    
    vector<TerrainSquare> terrain; //vector that holds the segment objects
    srand(time(0));
    for(int i = 0; i<levelSize ;i++){
        int randomHeight = rand() % 200 + 30;
        TerrainSquare temp(randomHeight,x,segmentWidth,i+1);
        terrain.push_back(temp);
        x += segmentWidth;
    }

    return terrain;
}
