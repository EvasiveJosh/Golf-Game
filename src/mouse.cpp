#include "mouse.h"

Mouse::Mouse()
{
    mouse = {GetScreenWidth()/2.0f - 30, GetScreenHeight()/2.0f - 30, 5, 5};
}

void Mouse::updateMousePosition()
{
    mousePos.x = GetMouseX();
    mousePos.y = GetMouseY();
    mouse.x = mousePos.x - mouse.width/2;
    mouse.y = mousePos.y - mouse.height/2;
}

const Rectangle& Mouse::mouseHitbox() const
{
    return mouse;
}

const Vector2& Mouse::position() const
{
    return mousePos;
}