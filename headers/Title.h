#ifndef TITLE_H
#define TITLE_H

#include <SFML/Graphics.hpp>

class Player;

class Title{
    private:
    sf::Text title;


    public:
    Title(std::string name,float pos);
    void draw();
    bool mouseClicked(int x, int y);
    };

#endif