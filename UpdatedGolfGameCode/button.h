#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "Mouse.h"
#include <string>
#include "screenSizeTransfer.h"

class Button
{
    private:
        std::string label;
        Rectangle bounds;
        //Returns a rectangle that surrounds the text
        Rectangle labelBounds(const std::string& text, int font, int posX, int posY);
    public:
        Button(const std::string& label, int font, int posX, int posY);
        Button(const std::string& label, Rectangle buttonDimensions);
        bool isHovered(const Mouse& mouse) const;
        const std::string& getLabel() const;
        const Rectangle& getBounds() const;
        //Used for moving objects
        void updateButtonBounds(Rectangle newButtonDimensions);
};

#endif