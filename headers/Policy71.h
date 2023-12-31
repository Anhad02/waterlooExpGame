#ifndef POLICY71_H
#define POLICY71_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player;

class Policy71{
    private:
    sf::CircleShape bullet;
    float bullet_time;
    float enemy_speed;


    public:
    Policy71();
    void movement(Player &player);
    void draw();
    void decrementTimer();
    void reset();
    };

#endif
