#ifndef PHYSICSCOLLISION_H
#define PHYSICSCOLLISION_H

#include "physicsObject.h"
#include "ball.h"
#include "rectangle.h"

class PhysicsCollision {
public:
    bool checkCollision(PhysicsObject* obj1, PhysicsObject* obj2);
    void handleCollision(PhysicsObject* obj1, PhysicsObject* obj2);

private:
    bool checkCircleRectCollision(Ball* ball, Rect* rect);
    bool checkCircleCircleCollision(Ball* ball1, Ball* ball2);
    bool checkRectRectCollision(Rect* rect1, Rect* rect2);
};

#endif
