#ifndef POLICY71_H
#define POLICY71_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player;

class Policy71{
    private:
    sf::Sprite bullet;
    sf::Text policy_text;
    float enemy_speed;
    float length;
    sf::Vector2f direction;
    sf::Vector2f moved_distance;
    double animationFrames;


    public:
    Policy71();
    void movement(Player &player);
    void draw();
    void reset();
    void death();
    void calculateConstants(Player &player);
    };

#endif
