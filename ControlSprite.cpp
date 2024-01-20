#include "headers/ControlSprite.h"

ControlSprite::ControlSprite()
{
    if (!control_texture.loadFromFile("./Textures/controls.png"))
    {
        std::cerr << "Texture not loaded";
    }
    controls.setTexture(control_texture);
    controls.setPosition(50,100);
}

void ControlSprite::draw()
{
    window.draw(controls);
}