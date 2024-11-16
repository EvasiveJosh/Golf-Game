#include <iostream>
#include "terrain.h"

using namespace std;

TerrainSquare::TerrainSquare(int h, int X, int w, int i){
    height = h;
    posX = X;
    width = w;
    id = i;
}
void TerrainSquare::DrawSquare(TerrainSquare sq){
    DrawRetangle(sq.posX, GRASS_HEIGHT, sq.width, sq.height, GREEN);
}
int TerrainSquare::getHeight(){
    return height;
}
int TerrainSquare::getPosX(){
    return posX;
}
int TerrainSquare::getId(){
    return id;
}

void Terrain::DrawTerrain()
