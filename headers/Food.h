#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

class Player;
class Score;

class Food
{
private:
    sf::Sprite food;

public:
    Food();
    bool is_visible_food = true;
    float food_timer;
    sf::Sprite getFood();
    void foodSpawn(Player &player, Score &score);
    void decrementTimer();
    void draw();
    void setPosition(int x, int y);
    void reset();
};

#endif
