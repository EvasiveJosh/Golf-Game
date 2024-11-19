#ifndef MATCH_H
#define MATCH_H

#include <vector>
#include <string>
#include <stdexcept>
#include "raylib.h"
#include "mouse.h"
#include "button.h"
#include "textureClass.h"
#include "screenSizeTransfer.h"
#include "GuiEnum.h"
#include "ball.h"

//Parent class for singleplayerMatch and multiplayerMatch
class Match
{
    protected:
        int difficulty;
        int wind;
        bool endlessMode;
        Mouse mouse;
        std::vector<Button> buttons;
        TextureClass textures;
        Ball golfball;
        bool end;
    public:
        virtual ~Match() = default;
        //Pure virtual functions that every menu class should have
        //Handles displaying
        virtual void draw() = 0;
        //Does any necessary operations before drawing (needs to update mouse position)
        virtual GuiEvent updateLogic() = 0;
        //Draws the mouse and buttons hitboxes to the screen.
        virtual void drawDebug() = 0;
        //Resumes the game
        virtual void resume() = 0;

        //Adds a button based off text
        void addButton(const std::string& label, int font, int posX, int posY);
        //Adds a button based off a rectangle
        void addButton(const std::string& label, Rectangle rec);

        int amountOfButtons() const;
        const Button& getButton(std::string& label);
        //Should really be called buttonHovered
        int buttonClicked() const;

        //Utility functions for menus (base coordinates of the CoordinateTransfer mapping are used)
        //Returns the x position that centers the text on the screen (no matter the screen dimensions)
        int centerTextX(const std::string& text, int font);
        //Returns the x position that centers the text on the screen (no matter the screen dimensions)
        int centerTextY(const std::string& text, int font);
        //Returns a rectangle that surrounds the text with some padding
        Rectangle surroundTextPad(const std::string& text, int font, int posX, int posY);
};

#endif

