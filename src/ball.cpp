// Game.cpp
#include "ball.h"

Ball::Ball()
{
    ballPosition = {BALL_RADIUS + 80, sst::baseY - BALL_RADIUS - GRASS_HEIGHT };
    previousStartPosition = ballPosition;
    velocity = { 0, 0 };
    isRolling = false;
    isDragging = false;
    isStopped = true;
    shotCount = 0;
    bool isOutOfBounds = false;
    ballColor = WHITE;
}

Ball::Ball(CLITERAL(Color) color)
{
    ballPosition = {BALL_RADIUS + 80, sst::baseY - BALL_RADIUS - GRASS_HEIGHT };
    previousStartPosition = ballPosition;
    velocity = { 0, 0 };
    isRolling = false;
    isDragging = false;
    isStopped = true;
    shotCount = 0;
    bool isOutOfBounds = false;
    ballColor = color;
}

void Ball::draw()
{
    // Draw ball
    DrawCircleV({sst::cxf(ballPosition.x), sst::cyf(ballPosition.y)}, sst::cx(BALL_RADIUS), ballColor);
    DrawCircleLines(sst::cxf(ballPosition.x), sst::cyf(ballPosition.y), sst::cx(BALL_RADIUS), BLACK);

    // Draw drag line
    if (isDragging) {
        DrawLineV(
            {startDrag.x, startDrag.y},
            {currentDrag.x, currentDrag.y},
            DARKGRAY
        );
    }
}

void Ball::drawDebug()
{
    //Draw minimum height terrain lines
    int font = 30;
    DrawRectangleLines(sst::cx(0), sst::cyf(sst::baseY - GRASS_HEIGHT), sst::cx(sst::baseX), sst::cyf(GRASS_HEIGHT), BLACK);
    DrawText(TextFormat("Shots: %d", shotCount), sst::cx(0), sst::cy(sst::baseY - 100), sst::cx(font), BLACK);
    DrawText(TextFormat("isRolling: %i", static_cast<int>(isRolling)), sst::cx(0), sst::cy(sst::baseY - 50), sst::cx(font), BLACK);
}

void Ball::updatePhysics()
{
    isStopped = (velocity.x == 0 && velocity.y == 0);

    if (!isDragging)
    {
        ballPosition.x += velocity.x;
        ballPosition.y += velocity.y;

        //Apply Gravity
        velocity.y += GRAVITY;

        //Check for collisions
        checkCollisions();

        //Apply friction if rolling
        applyFriction();
    }
}

void Ball::checkCollisions()
{
    // Base screen dimensions
    float screenWidthBase = sst::baseX;
    float screenHeightBase = sst::baseY;

    // Minimum height collision
    if (ballPosition.y > screenHeightBase - GRASS_HEIGHT - BALL_RADIUS) 
    {
        ballPosition.y = screenHeightBase - GRASS_HEIGHT - BALL_RADIUS;

        if (fabs(velocity.y) < STOP_THRESHOLD) 
        {
            velocity.y = 0;
            isRolling = true;
        } 
        else 
        {
            isRolling = false;
            velocity.y *= -DAMPING;
        }
    }

    // Side wall collisions
    if (ballPosition.x < BALL_RADIUS) 
    {
        ballPosition.x = BALL_RADIUS;
        velocity.x *= -DAMPING;
    } 
    else if (ballPosition.x > screenWidthBase - BALL_RADIUS) 
    {
        ballPosition.x = screenWidthBase - BALL_RADIUS;
        velocity.x *= -DAMPING;
    }

    // Top wall collision
    if (ballPosition.y < BALL_RADIUS) 
    {
        ballPosition.y = BALL_RADIUS;
        velocity.y *= -DAMPING;
    }
}

void Ball::applyFriction()
{
    if (isRolling) 
    {
        velocity.x *= FRICTION;
        if (fabs(velocity.x) < 0.1f) //Once the ball has speed less than 0.1, force it to stop
        {
            velocity.x = 0;
        }
    }    
}

void Ball::updateLogic()
{
    shotCount++;
    previousStartPosition = ballPosition;
}

Vector2 Ball::getBallPosition()
{
    return {ballPosition.x, ballPosition.y};
}

Vector2 Ball::getVelocity()
{
    return {velocity.x, velocity.y};
}

void Ball::updateVelocity(Vector2 newVel)
{
    velocity = newVel;
}

int Ball::getShotCount() const
{
    return shotCount;
}