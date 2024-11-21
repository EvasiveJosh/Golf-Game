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
#include "flag.h"

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
        Flag flag;
        Ball golfball;
        bool isPaused;
        float defaultZoom;
    public:
        SingleplayerMatch(std::vector<int> info);
        void draw() override;
        void drawDebug() override;
        GuiEvent updateLogic() override;
        void resume() override;
        bool cameraShouldFollowBall;
        bool cameraShouldCenter;
        float smoothingFactor;
        void updateCamera();
        Camera2D camera;
        int getShotCount() const;
};

#endif