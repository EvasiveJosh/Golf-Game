#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "raylib.h"
#include "physicsConstants.h"

class PhysicsObject {
    private:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        float rotation;
        float angularVelocity;
        float angularAcceleration;
        enum Shape shape;

        bool hasGravity;

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

        Vector2 getPosition();
        Vector2 getVelocity();
        Vector2 getAcceleration();
        float getRotation();
        float getAngularVelocity();
        float getAngularAcceleration();
        enum Shape getShape();
};

#endif