#ifndef CONTROLSPRITE_H
#define CONTROLSPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Global.h"

class ControlSprite
{
private:
    sf::Sprite controls;

public:
    ControlSprite();
    void draw();
};

#endif
