#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class Player{
    private:
    sf::Sprite modal;
    int player_width;
    int player_length;
    float animationFrames;

    public:
    Player();
    sf::Sprite getPlayer();
    int getWidth();
    int getLength();
    void movement();
    sf::Vector2f getPos();
    void draw();
    void reset();

};
#endif