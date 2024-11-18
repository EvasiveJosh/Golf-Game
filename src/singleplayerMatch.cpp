#include "singleplayerMatch.h"

SingleplayerMatch::SingleplayerMatch(std::vector<int> info)
{
    //Settings for the match, so far serve no purpose
    this->difficulty = info[0];
    this->wind = info[1];
    this->endlessMode = !info[2];
    end = false;
    Terrain terrainGenerator;
    std::vector<TerrainSquare> terrain = terrainGenerator.DrawTerrain(difficulty);
    //Load mouse
    mouse = Mouse();
    //Load golfball
    golfball = Ball(WHITE);

    //Create golfballButton
    Vector2 ballPosVec = golfball.getBallPosition();
    addButton("Ball", {ballPosVec.x - 13, ballPosVec.y - 13, 28, 28});
    //Create Hole at ground level at opposite playing side
    addButton("Hole", {sst::baseX - 100, sst::baseY - GRASS_HEIGHT - 10, 20, 20});
}

void SingleplayerMatch::draw()
{
    // //Draw some default terrain
    // DrawRectangle(sst::cx(0), sst::cyf(sst::baseY - GRASS_HEIGHT), sst::cx(sst::baseX), sst::cyf(GRASS_HEIGHT), GREEN);

    DrawCircle(10,10,3,RED);
    //Draw some default sky
    DrawRectangle(sst::cx(0), sst::cy(0), sst::cx(sst::baseX), sst::cyf(sst::baseY - GRASS_HEIGHT), BLUE);
    //Draw some default hole
    DrawRectangle(sst::cx(sst::baseX - 100), sst::cy(sst::baseY - GRASS_HEIGHT - 10), sst::cx(20), sst::cx(20), MAGENTA);

    // golfball.draw();
    for (const TerrainSquare& square : terrain) {
        DrawRectangle(square.getPosX(), sst::baseY - square.getHeight(), square.getWidth(), square.getHeight(), GREEN);
    }
    // Draw other elements (e.g., golfball)
    golfball.draw();
}

void SingleplayerMatch::drawDebug()
{
    golfball.drawDebug();
    //Draw mouse hitbox
    DrawRectangleRec(mouse.mouseHitbox(), PURPLE);
    //Draw button hitboxes
    for (int i = 0; i < amountOfButtons(); i++)
    {
        DrawRectangleLinesEx(buttons[i].getBounds(), 5, PURPLE);
    }
    //Show current selection
    int font = 20;
    DrawText(TextFormat("Buttons[%i]", buttonClicked()), 0, 0, sst::cx(font), BLACK);
    DrawText(TextFormat("Wind: %i", wind), 0, sst::cy(40), sst::cx(font), BLACK);
}

GuiEvent SingleplayerMatch::updateLogic()
{
    //General logic to be checked here
    mouse.updateMousePosition();
    golfball.updatePhysics();
    Vector2 ballPosVec = golfball.getBallPosition();
    buttons[0].updateButtonBounds({ballPosVec.x - 13, ballPosVec.y - 13, 28, 28});

    //Check is ball has stopped on hole, if so, you won!
    if (CheckCollisionRecs(buttons[0].getBounds(), buttons[1].getBounds()) && golfball.isStopped)
    {
        end = true;
        return OpenStartingMenu; //To be changed
    }

    //Launch the ball check
    if (golfball.isStopped)
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !golfball.isDragging)
        {
            if (buttonClicked() == 0)
            {
                golfball.isDragging = true;
                golfball.startDrag = golfball.getBallPosition();
                golfball.currentDrag = mouse.position();
                golfball.updateVelocity({0,0});
            }
        } 
        else if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && golfball.isDragging)
        {
            golfball.currentDrag = mouse.position();
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && golfball.isDragging)
        {
            Vector2 dragVector = {golfball.startDrag.x - golfball.currentDrag.x, golfball.startDrag.y - golfball.currentDrag.y};
            golfball.updateVelocity({dragVector.x * LAUNCH_SCALE, dragVector.y * LAUNCH_SCALE});
            golfball.isDragging = false;
            if (wind == 3)
                golfball.isRolling = true; //A neat little thing happens, the ball slows down drastically in the x direction
            else
                golfball.isRolling = false;
            golfball.updateLogic();
        }
    }
    return Nothing;
}
