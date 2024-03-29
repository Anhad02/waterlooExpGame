#include "./headers/Title.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "./headers/Global.h"

Title::Title(std::string name, float pos)
{
    if (!font.loadFromFile("./arial.ttf"))
    {
        std::cerr << "Error loading font\n";
        return;
    }
    title.setFont(font);
    title.setString(name);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    sf::FloatRect textBounds = title.getLocalBounds();
    title.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top);
    title.setPosition(screen_width / 2.0, pos);
    title.setOutlineThickness(3.0);
}

void Title::draw()
{
    window.draw(title);
}

void Title::setText(std::string text)
{
    title.setString(text);
}

void Title::setCharSize(int size)
{
    title.setCharacterSize(size);
}

void Title::centerText()
{
    sf::FloatRect textBounds = title.getLocalBounds();
    title.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top);
    title.setPosition(screen_width / 2.0, title.getPosition().y);
}

bool Title::mouseClicked(int x, int y)
{
    if (title.getGlobalBounds().contains(x, y))
    {
        return true;
    }
    return false;
}

void Title::setPosition(int x, int y)
{
    title.setPosition(x, y);
}