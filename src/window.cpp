#include "window.h"
#include <iostream>

void Window::start(){
    InitWindow(this->windowWidth, this->windowHeight, "Golf Game");
    SetTargetFPS(60);

    this->monitorWidth = GetMonitorWidth(0);
    this->monitorHeight = GetMonitorHeight(0);
}

void Window::changeSize(int x, int y){
    SetWindowSize(x, y);
    SetWindowPosition(this->monitorWidth/2 - x/2, this->monitorHeight/2 - y/2);

    std::cout << monitorWidth << std::endl;

    this->windowWidth = x;
    this->windowHeight = y;
}

void Window::close(){
    CloseWindow();
}