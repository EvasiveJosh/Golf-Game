#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <stdexcept>
#include "raylib.h"
#include "mouse.h"
#include "button.h"
#include "textureClass.h"
#include "screenSizeTransfer.h"
#include "GuiEnum.h"

/*
Notes:
- Constructor must initialize screen variables and call the buttons constructor
- load function must intialize textures, mouse, buttons and isLoaded
- FIX center_y
- ADD DESCRIPTION FOR ADDBUTTON
*/

/*
TODO:
- Change beforeDraw and drawDebug to have part of those done by default in Menu class
*/

#define MAX_NAME_INPUT 10
#define MAX_IPADDRESS_INPUT 20

class Menu
{
    protected:
        TextureClass textures;
        Mouse mouse;
        std::vector<Button> buttons;
        char username[MAX_NAME_INPUT + 1] = "\0"; //Used only by some menu classes (such as joinMultiplayerMenu)
        char hostname[MAX_NAME_INPUT + 1] = "\0"; //Used only by some menu classes (such as joinMultiplayerMenu)
        char ipAddress[MAX_IPADDRESS_INPUT + 1] = "\0"; //Used only by some menu classes (such as joinMultiplayerMenu)
    public:
        virtual ~Menu() = default;
        //Pure virtual functions that every menu class should have
        //Handles displaying
        virtual void draw() = 0;
        //Does any necessary operations before drawing (needs to update mouse position)
        virtual GuiEvent updateMenuLogic() = 0;
        //Draws the mouse and buttons hitboxes to the screen.
        virtual void drawDebug() = 0;

        //Non-pure virtual functions, they are implemented only by certain classes, they by default do nothing
        //Returns the corresponding strings
        virtual std::string getUserName();
        virtual std::string getHostName();
        virtual std::string getIpAddress();
        virtual std::vector<int> getInformation();
        virtual const float& getVolumeLevel(); //Used in generalSettingsMenu

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