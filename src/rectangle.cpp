#include "rectangle.h"
#include "screenSizeTransfer.h"

Rect::Rect(int w, int h, CLITERAL(Color) color){
    this->width = w;
    this->height = h;

    this->fill_color = color;

    this->setPosition({100,100});
    this->setVelocity({0, 0});
    this->setAcceleration({0, 0});
    this->setRotation(0);
    this->setAngularVelocity(0);
    this->setShape(Shape::RECTANGLE);

}

void Rect::draw(){
    
    DrawRectangle(sst::cx(this->getPosition().x), sst::cyf(this->getPosition().y), sst::cx(this->getPosition().x + this->width), sst::cy(this->getPosition().y + this->height), this->fill_color);
}