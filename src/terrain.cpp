#include <iostream>
#include "terrain.h"

using namespace std;

TerrainSquare::TerrainSquare(int h, int X, int w, int i){
    height = h;
    posX = X;
    width = w;
    id = i;

    DrawRectangle(X, GRASS_HEIGHT, w, h, GREEN);
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
    srand(time(0));
    // for(int i = 0; i<levelSize ;i++){
    //     int randomHeight = rand() % 20 + 5;
    //     terrain.emplace_back(randomHeight, x, 5, i + 1);
    //     x+=5;
    // }
    for (int i = 0; i < levelSize; i++) {
        int randomHeight = rand() % 100 + 20; // Increased height range for visibility
        int width = 50; // Adjust width to be more visible
        terrain.emplace_back(randomHeight, x, width, i + 1); // Create square
        x += width; // Offset x by the width to avoid overlap
    }

    return terrain;
}
