#ifndef JOINMULTIPLAYERMENU_H
#define JOINMULTIPLAYERMENU_H

#include <iostream>
#include "menu.h"

enum JoinMultiplayerMenuButton
{
    JMMB_Back,
    JMMB_MyUsername,
    JMMB_HostUsername,
    JMMB_IPAddress,
    JMMB_Join
};

class JoinMultiplayerMenu : public Menu
{
    private:
        int usernameLetterCount;
        int hostnameLetterCount;
        int ipAddressLetterCount;
        Rectangle usernameTextBox;
        Rectangle hostnameTextBox;
        Rectangle ipAddressTextBox;
        bool isModifyingUsername;
        bool isModifyingHostname;
        bool isModifyingIPAddress;
    public:
        JoinMultiplayerMenu();
        void draw() override;
        GuiEvent updateMenuLogic() override;
        void drawDebug() override;
        std::string getUserName() override;
        std::string getHostName() override;
        std::string getIpAddress() override;
    private:
        void modifyUsername();
        void modifyHostname();
        void modifyIPAddress();
};

#endif