#include "physicsCollision.h"
#include "raymath.h"
#include <iostream>

bool PhysicsCollision::checkCollision(PhysicsObject* obj1, PhysicsObject* obj2) {

    enum Shape shape1 = obj1->getShape();
    enum Shape shape2 = Shape::RECTANGLE;

    if (shape1 == Shape::CIRCLE && shape2 == Shape::CIRCLE) {
        return checkCircleCircleCollision(static_cast<Ball*>(obj1), static_cast<Ball*>(obj2));
    } else if (shape1 == Shape::CIRCLE && shape2 == Shape::RECTANGLE) {
        return checkCircleRectCollision(static_cast<Ball*>(obj1), static_cast<Rect*>(obj2));
    } else if (shape1 == Shape::RECTANGLE && shape2 == Shape::RECTANGLE) {
        return checkRectRectCollision(static_cast<Rect*>(obj1), static_cast<Rect*>(obj2));
    }

    return false;
}

void PhysicsCollision::handleCollision(PhysicsObject* obj1, PhysicsObject* obj2) {
    if (checkCollision(obj1, obj2)) {
        std::cout << "Test" << std::endl;
        Vector2 velocity1 = obj1->getVelocity();
        Vector2 velocity2 = obj2->getVelocity();

        obj1->setVelocity(Vector2Scale(velocity1, -1));
        obj2->setVelocity(Vector2Scale(velocity2, -1));
    }
}

bool PhysicsCollision::checkCircleCircleCollision(Ball* ball1, Ball* ball2) {
    Vector2 pos1 = ball1->getPosition();
    Vector2 pos2 = ball2->getPosition();
    float radius1 = BALL_RADIUS;
    float radius2 = BALL_RADIUS;

    return CheckCollisionCircles(pos1, radius1, pos2, radius2);
}

bool PhysicsCollision::checkCircleRectCollision(Ball* ball, Rect* rect) {
    Vector2 ballPos = ball->getPosition();
    float ballRadius = BALL_RADIUS;
    
    Vector2 rectPos = rect->getPosition();
    int rectWidth = rect->getWidth();
    int rectHeight = rect->getHeight();

    return CheckCollisionCircleRec(ballPos, ballRadius, {rectPos.x, rectPos.y, (float)rectWidth, (float)rectHeight});
}

bool PhysicsCollision::checkRectRectCollision(Rect* rect1, Rect* rect2) {
    Vector2 pos1 = rect1->getPosition();
    Vector2 pos2 = rect2->getPosition();

    return CheckCollisionRecs(
        {pos1.x, pos1.y, (float)rect1->getWidth(), (float)rect1->getHeight()},
        {pos2.x, pos2.y, (float)rect2->getWidth(), (float)rect2->getHeight()}
    );
}
