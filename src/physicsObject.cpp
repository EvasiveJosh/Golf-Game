#include "physicsObject.h"

void PhysicsObject::update(){
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;

    this->velocity.x += this->acceleration.x;
    this->velocity.y += this->acceleration.y;

    this->rotation += this->angularVelocity;

    this->angularAcceleration += this->angularAcceleration;
}


void PhysicsObject::setPosition(Vector2 newPosition){
    this->position = newPosition;
}

void PhysicsObject::setVelocity(Vector2 newVelocity){
    this->velocity = newVelocity;
}

void PhysicsObject::setAcceleration(Vector2 newAcceleration){
    this->acceleration = newAcceleration;
}

void PhysicsObject::setRotation(float newRotation){
    this->rotation = newRotation;
}

void PhysicsObject::setAngularVelocity(float newAngularVelocity){
    this->angularVelocity = newAngularVelocity;
}

void PhysicsObject::setAngularAcceleration(float newAngularAcceleration){
    this->angularAcceleration = newAngularAcceleration;
}

void PhysicsObject::setShape(enum Shape newShape){
    this->shape = newShape;
}

void PhysicsObject::setGravity(bool flag){
    this->hasGravity = flag;
}

Vector2 PhysicsObject::getPosition(){
    return this->position;
}

Vector2 PhysicsObject::getVelocity(){
    return this->velocity;
}

Vector2 PhysicsObject::getAcceleration(){
    return this->acceleration;
}

float PhysicsObject::getRotation(){
    return this->rotation;
}

float PhysicsObject::getAngularVelocity(){
    return this->angularVelocity;
}

float PhysicsObject::getAngularAcceleration(){
    return this->angularAcceleration;
}

enum Shape PhysicsObject::getShape(){
    return this->shape;  // Added to return the shape of the object
}