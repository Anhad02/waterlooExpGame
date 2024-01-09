#ifndef COURSES_H
#define COURSES_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player;

class Courses{
    private:
    std::vector<sf::Sprite> enemies;
    std::vector<sf::Text> enemy_text;
    std::vector<sf::Vector2f> enemy_speed;
    int enemies_size;

    public:
    Courses();
    void change_type(int level);
    void movement(Player &player);
    void draw();
    void reset();
    };

#endif
