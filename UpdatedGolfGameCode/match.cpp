#include "match.h"

void Match::addButton(const std::string& label, int font, int posX, int posY)
{
    buttons.push_back(Button(label, font, posX, posY));
}

void Match::addButton(const std::string& label, Rectangle rec)
{
    buttons.push_back(Button(label ,rec));
}

int Match::amountOfButtons() const
{
    return buttons.size();
}

const Button& Match::getButton(std::string& label)
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

int Match::centerTextX(const std::string& text, int font)
{
    return (sst::baseX/2) - (MeasureText(text.c_str(), (font))/2);
}

int Match::centerTextY(const std::string& text, int font)
{
    return (sst::baseY/2);
}

Rectangle Match::surroundTextPad(const std::string& text, int font, int posX, int posY)
{
    float rectX = sst::cx(posX);
    float rectY = sst::cy(posY);
    float width = MeasureText(text.c_str(), sst::cx(font));
    Rectangle rec = {rectX - sst::cx(10), rectY - sst::cy(10), width + sst::cx(10), (float)sst::cy(font) + sst::cy(10)};
    return rec;
}

int Match::buttonClicked() const
{
    for(int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].isHovered(mouse))
            return i;
    }
    return -1;
}