#ifndef PSCYCH_H
#define PSCYCH_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player;

class Psych{
    private:
    sf::CircleShape psych_enemy;
    float enemy_speed;
    int random_y;


    public:
    Psych();
    void movement(Player &player);
    void draw();
    void decrementTimer();
    void reset();
    };

#endif
