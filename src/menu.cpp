#include "menu.h"

void Menu::addButton(const std::string& label, int font, int posX, int posY)
{
    buttons.push_back(Button(label, font, posX, posY));
}

void Menu::addButton(const std::string& label, Rectangle rec)
{
    buttons.push_back(Button(label ,rec));
}

int Menu::amountOfButtons() const
{
    return buttons.size();
}

const Button& Menu::getButton(std::string& label)
{
    if (buttons.size() == 0)
        throw std::runtime_error("No buttons available in the menu");
    
    for(int i = 0; i < buttons.size(); i++)
    {
        if (label.compare(buttons[i].getLabel()) == 0)
            return buttons[i];
    }
    throw std::runtime_error("No such button exists");
}

int Menu::centerTextX(const std::string& text, int font)
{
    return (sst::baseX/2) - (MeasureText(text.c_str(), (font))/2);
}

int Menu::centerTextY(const std::string& text, int font)
{
    return (sst::baseY/2);
}

Rectangle Menu::surroundTextPad(const std::string& text, int font, int posX, int posY)
{
    float rectX = sst::cx(posX);
    float rectY = sst::cy(posY);
    float width = MeasureText(text.c_str(), sst::cx(font));
    Rectangle rec = {rectX - sst::cx(10), rectY - sst::cy(10), width + sst::cx(10), (float)sst::cy(font) + sst::cy(10)};
    return rec;
}

int Menu::buttonClicked() const
{
    for(int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].isHovered(mouse))
            return i;
    }
    return -1;
}

std::string Menu::getUserName()
{
    //Does nothing by default
    return "";
}

std::string Menu::getHostName()
{
    //Does nothing by default
    return "";
}

std::string Menu::getIpAddress()
{
    //Does nothing by default
    return "";    
}

std::vector<int> Menu::getInformation()
{
    //Does nothing by default
    return {-1};
}

const float& Menu::getVolumeLevel()
{
    //Does nothing by default
    return 0.0f;
}


