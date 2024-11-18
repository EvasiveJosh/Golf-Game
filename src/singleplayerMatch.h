#ifndef SINGLEPLAYERMATCH_H
#define SINGLEPLAYERMATCH_H

#include "raylib.h"
#include "GuiEnum.h"
#include "textureClass.h"
#include "button.h"
#include "mouse.h"
#include "ball.h"
#include "match.h"
#include "terrain.h"
#include "vector"

/*
TODO:
    - Implement wind (other than 3)
    - Implement difficulty
    - Implement endless mode
    - Implement terrain
    - When game ends, do something other than returning to main menu
*/

class SingleplayerMatch : public Match
{
    private:
        std::vector<TerrainSquare> terrain;
        TextureClass flag;
    public:
        SingleplayerMatch(std::vector<int> info);
        void draw() override;
        void drawDebug() override;
        GuiEvent updateLogic() override;
};

#endif