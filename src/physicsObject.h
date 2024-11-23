#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "raylib.h"
#include "physicsConstants.h"

class PhysicsObject {
    private:
        Vector2 position = {0, 0};
        Vector2 velocity = {0, 0};
        Vector2 acceleration = {0, 0};
        float rotation = 0.0f;
        float angularVelocity = 0.0f;
        float angularAcceleration = 0.0f;
        enum Shape shape;

        bool hasGravity = false;

    public:
        virtual void draw() = 0;
        void update();

        void setPosition(Vector2 newPosition);
        void setVelocity(Vector2 newVelocity);
        void setAcceleration(Vector2 newAcceleration);
        void setRotation(float newRotation);
        void setAngularVelocity(float newAngularVelocity);
        void setAngularAcceleration(float newAngularAcceleration);
        void setShape(enum Shape newShape);
        void setGravity(bool flag);

        Vector2 getPosition();
        Vector2 getVelocity();
        Vector2 getAcceleration();
        float getRotation();
        float getAngularVelocity();
        float getAngularAcceleration();
        enum Shape getShape();
};

#endif