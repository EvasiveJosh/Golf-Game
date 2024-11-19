#include <iostream>
#include "terrain.h"

using namespace std;

TerrainSquare::TerrainSquare(int h, int X, int w, int i){
    height = h;
    posX = X;
    width = w;
    id = i;
    // DrawRectangle(X, GRASS_HEIGHT, w, h, GREEN);
}
// void TerrainSquare::DrawSquare(TerrainSquare sq){
//     DrawRetangle(sq.posX, GRASS_HEIGHT, sq.width, sq.height, GREEN);
// }
int TerrainSquare::getHeight() const{
    return height;
}
int TerrainSquare::getPosX() const{
    return posX;
}
int TerrainSquare::getId() const{
    return id;
}
int TerrainSquare::getWidth() const{
    return width;
}

vector<TerrainSquare> Terrain::DrawTerrain(int difficulty){
    Ball golfball;
    Vector2 ballPosVec = golfball.getBallPosition();
    int levelSize = 0;
    if(difficulty == 0){ //difficulty easy
        levelSize = 8;
    }
    else if(difficulty == 1){ //difficulty medium
        levelSize = 10;
    }
    else{ //difficulty hard
        levelSize = 12;
    }
    int x = sst::cx(ballPosVec.x+50);
    vector<TerrainSquare> terrain; //vector that holds the segment objects
    srand(time(0));
    for(int i = 0; i<levelSize ;i++){
        int randomHeight = rand() % 150 + 30;
        int width = 100;
        TerrainSquare temp(randomHeight,x,width,i+1);
        terrain.push_back(temp);
        x += width;
    }

    return terrain;
}
