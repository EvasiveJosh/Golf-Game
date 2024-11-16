#ifndef SINGLEPLAYERMATCH_H
#define SINGLEPLAYERMATCH_H

#include "raylib.h"
#include "GuiEnum.h"
#include "textureClass.h"
#include "button.h"
#include "mouse.h"
#include "ball.h"
#include "match.h"

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
    public:
        SingleplayerMatch(int difficulty, int wind, bool endlessMode);
        void draw() override;
        void drawDebug() override;
        GuiEvent updateLogic() override;
};

#endif