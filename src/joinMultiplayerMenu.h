#ifndef JOINMULTIPLAYERMENU_H
#define JOINMULTIPLAYERMENU_H

#include <iostream>
#include "menu.h"

enum JoinMultiplayerMenuButton
{
    JMMB_Back,
    JMMB_MyUsername,
    JMMB_HostUsername,
    JMMB_Join
};

class JoinMultiplayerMenu : public Menu
{
    private:
        int usernameLetterCount;
        int hostnameLetterCount;
        Rectangle usernameTextBox;
        Rectangle hostnameTextBox;
        bool isModifyingUsername;
        bool isModifyingHostname;
    public:
        JoinMultiplayerMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
        std::string getUserName() override;
        std::string getHostName() override;
    private:
        void modifyUsername();
        void modifyHostname();
};

#endif