#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class Player{
    private:
    sf::RectangleShape modal;
    int player_width;
    int player_length;

    public:
    Player();
    sf::RectangleShape getPlayer();
    int getWidth();
    int getLength();
    void movement();
    sf::Vector2f getPos();
    void draw();
    void reset();

};
#endif