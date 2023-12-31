#ifndef COURSES_H
#define COURSES_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player;

class Courses{
    private:
    std::vector<sf::RectangleShape> enemies;
    std::vector<sf::Vector2f> enemy_speed;
    int enemies_size;

    public:
    Courses();
    void movement(Player &player);
    void draw();
    void reset();
    };

#endif
