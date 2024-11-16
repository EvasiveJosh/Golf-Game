#ifndef MOUSE_H
#define MOUSE_H

#include "raylib.h"

class Mouse
{
    private:
        Vector2 mousePos;
        Rectangle mouse;
    public:
        //Creates mouse and pos for mouse hitbox
        Mouse();
        //Returns a const reference containing the position of the mouse
        const Vector2& position() const;
        //Retuns a constant reference to the mouse hitbox
        const Rectangle& mouseHitbox() const;
        //Updates the position of the mouse
        void updateMousePosition();
};

#endif
