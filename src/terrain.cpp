#include <iostream>
#include "terrain.h"

using namespace std;

TerrainSquare::TerrainSquare(int h, int X, int w, int i){
    height = h;
    posX = X;
    width = w;
    id = i;

    DrawRetangle(X, GRASS_HEIGHT, w, h, GREEN);
}
// void TerrainSquare::DrawSquare(TerrainSquare sq){
//     DrawRetangle(sq.posX, GRASS_HEIGHT, sq.width, sq.height, GREEN);
// }
int TerrainSquare::getHeight(){
    return height;
}
int TerrainSquare::getPosX(){
    return posX;
}
int TerrainSquare::getId(){
    return id;
}

vector<TerrainSquare> Terrain::DrawTerrain(int difficulty){
    int levelSize = 0;
    if(difficulty == 0){ //difficulty easy
        levelSize = 2;
    }
    else if(difficulty == 1){ //difficulty medium
        levelSize = 4;
    }
    else{ //difficulty hard
        levelSize = 6;
    }
    int x = 0;
    vector<TerrainSquare> terrain; //vector that holds the segment objects

    for(int i = 0; i<levelSize ;i++){
        terrain.emplace_back(5, x, 5, i + 1);
        x+=5;
    }

    return terrain;
}
