#ifndef WINDOW_H
#define WINDOW_H

#include "raylib.h"

#define DEFAULT_WINDOW_X 1280
#define DEFAULT_WINDOW_Y 720


class Window{
    private:
        int monitorWidth;
        int monitorHeight;

        int windowWidth = DEFAULT_WINDOW_X;
        int windowHeight = DEFAULT_WINDOW_Y;

    public:
        void start();
        void changeSize(int x, int y);
        void close();
};


#endif