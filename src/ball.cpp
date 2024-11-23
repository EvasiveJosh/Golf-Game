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

Ball::Ball(CLITERAL(Color) color,int levelScale)
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
    this->scale = levelScale;
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
    DrawRectangleLines(sst::cx(0), sst::cyf(sst::baseY - GRASS_HEIGHT), sst::cx(sst::baseX*scale), sst::cyf(GRASS_HEIGHT), BLACK);
    DrawText(TextFormat("Shots: %d", shotCount), sst::cx(0), sst::cy(sst::baseY - 100), sst::cx(font), BLACK);
    DrawText(TextFormat("isRolling: %i", static_cast<int>(isRolling)), sst::cx(0), sst::cy(sst::baseY - 50), sst::cx(font), BLACK);
}

void Ball::updatePhysics(const std::vector<TerrainSquare>& terrain)
{
    isStopped = (velocity.x == 0 && velocity.y == 0);

    if (!isDragging)
    {
        ballPosition.x += velocity.x;
        ballPosition.y += velocity.y;

        //Apply Gravity
        velocity.y += GRAVITY;

        //Check for collisions
        checkCollisions(terrain);

        //Apply friction if rolling
        applyFriction();
    }
}

void Ball::checkCollisions(const std::vector<TerrainSquare>& terrain)
{
    // Base screen dimensions
    float screenWidthBase = sst::baseX * scale;
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

    // Terrain collisions
    for (const TerrainSquare& square : terrain) 
    {
        int squareX = square.getPosX();
        int squareWidth = square.getWidth();
        int squareY = sst::baseY - GRASS_HEIGHT - square.getHeight();
        int squareHeight = square.getHeight();

        const float edgeTolerance = 0.01f;

        // Check if the ball is intersecting the terrain square
        bool withinXBounds = (ballPosition.x + BALL_RADIUS - edgeTolerance > squareX) &&
                            (ballPosition.x - BALL_RADIUS + edgeTolerance < squareX + squareWidth);
        bool withinYBounds = (ballPosition.y + BALL_RADIUS - edgeTolerance > squareY) &&
                            (ballPosition.y - BALL_RADIUS + edgeTolerance < squareY + squareHeight);

        if (withinXBounds && withinYBounds) 
        {
            // Determine overlap distances for all sides
            float overlapTop = (squareY - (ballPosition.y + BALL_RADIUS));
            float overlapBottom = ((ballPosition.y - BALL_RADIUS) - (squareY + squareHeight));
            float overlapLeft = (squareX - (ballPosition.x + BALL_RADIUS));
            float overlapRight = ((ballPosition.x - BALL_RADIUS) - (squareX + squareWidth));

            // Find smallest overlap to resolve collision
            float smallestOverlap = fmin(fabs(overlapTop), fmin(fabs(overlapBottom), fmin(fabs(overlapLeft), fabs(overlapRight))));

            if (smallestOverlap == fabs(overlapTop)) 
            {
                // Collision with the top of the square
                ballPosition.y = squareY - BALL_RADIUS;
                velocity.y = (fabs(velocity.y) < STOP_THRESHOLD) ? 0 : velocity.y * -DAMPING;
                isRolling = (velocity.y == 0);
            } 
            else if (smallestOverlap == fabs(overlapBottom)) 
            {
                // Collision with the bottom of the square
                ballPosition.y = squareY + squareHeight + BALL_RADIUS;
                velocity.y *= -DAMPING;
            } 
            else if (smallestOverlap == fabs(overlapLeft)) 
            {
                // Collision with the left side of the square
                ballPosition.x = squareX - BALL_RADIUS;
                velocity.x *= -DAMPING;
            } 
            else 
            {
                // Collision with the right side of the square
                ballPosition.x = squareX + squareWidth + BALL_RADIUS;
                velocity.x *= -DAMPING;
            }

            // Prevent corner conflicts by damping velocity on both axes if required
            if (fabs(smallestOverlap) < edgeTolerance) 
            {
                velocity.x *= DAMPING;
                velocity.y *= DAMPING;
            }
        }
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