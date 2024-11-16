#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "math.h"
#include "screenSizeTransfer.h"

/*
Once terrain class exists, send the terrain position to updatePhysics() and through checkCollisions
applyFriction will also need to be overhauled to incorporate different terrain friction (if we are doing that)
*/

// Constants (built with standard 1280x720 res)
const float GRAVITY = 0.5f;
const float DAMPING = 0.3f;
const float FRICTION = 0.95f;
const float STOP_THRESHOLD = 5.0f;
const float LAUNCH_SCALE = 0.25f;
const float BALL_RADIUS = 12.0f;
const float GRASS_HEIGHT = 160.0f; //Minimum height

class Ball
{
    private:
        //Position and movement variables
        Vector2 ballPosition;
        Vector2 velocity;
        Vector2 previousStartPosition;
        bool isOutOfBounds;

        //Stats
        int shotCount;

        //Misc
        CLITERAL(Color) ballColor;
    
    public:
        //Draggin stuff
        Vector2 startDrag;
        Vector2 currentDrag;
        bool isDragging;
        bool isRolling;
        bool isStopped;

        Ball();
        Ball(CLITERAL(Color) color);
        //Draws the ball on the screen
        void draw();
        void drawDebug();
        void checkCollisions();
        void applyFriction();
        void updatePhysics();
        //Just used to set the previousStartPosition vector and shot count
        void updateLogic(); 
        void updateVelocity(Vector2 newVel);
        //ResetGame needs to be overhauled
        Vector2 getBallPosition();
};

#endif
