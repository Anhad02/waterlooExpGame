#ifndef POLICY71_H
#define POLICY71_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player;

class Policy71{
    private:
    sf::CircleShape bullet;
    float enemy_speed;
    float length;
    sf::Vector2f direction;
    sf::Vector2f moved_distance;


    public:
    Policy71();
    void movement(Player &player);
    void draw();
    void reset();
    void calculateConstants(Player &player);
    };

#endif
