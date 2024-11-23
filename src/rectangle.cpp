#include "rectangle.h"
#include "screenSizeTransfer.h"

Rect::Rect(){
    this->setShape(Shape::RECTANGLE);
}


void Rect::draw(){
    DrawRectangle(
        sst::cx(this->getPosition().x),
        sst::cy(this->getPosition().y), 
        sst::cx(this->width),
        sst::cy(this->height), 
        this->fill_color);
}

void Rect::setWidth(int w){
    this->width = w;
}

void Rect::setHeight(int h){
    this->height = h;
}

void Rect::setColor(CLITERAL(Color) c){
    this->fill_color = c;
}

int Rect::getWidth(){
    return this->width;
}

int Rect::getHeight(){
    return this->height;
}