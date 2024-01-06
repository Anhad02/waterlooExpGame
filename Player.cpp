#include "./headers/Player.h"
#include "./headers/Global.h"

Player::Player(){
    player_width=80.0;
    player_length=80.0;
    modal=sf::RectangleShape(sf::Vector2f(player_width, player_length));
    modal.setFillColor(sf::Color::Blue);
    sf::FloatRect modalBounds=modal.getLocalBounds();
    modal.setOrigin(modalBounds.left + modalBounds.width/2.0,modalBounds.top+modalBounds.height/2.0);
    modal.setPosition(sf::Vector2f(screen_width/2, screen_length-player_length));
}

sf::RectangleShape Player::getPlayer() {
    return modal;
}

int Player::getWidth() {
    return player_width;
}

int Player::getLength() {
    return player_length;
}

void Player::movement() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            modal.move(sf::Vector2f(-0.08 * dt, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            modal.move(sf::Vector2f(0.08 * dt, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& modal.getPosition().y<=screen_length-player_length)
            modal.move(sf::Vector2f(0, 0.08 * dt));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && modal.getPosition().y>=0)
            modal.move(sf::Vector2f(0, -0.08 * dt));
        //Player goes out of bonds 
        if(modal.getPosition().x>(screen_width))
            modal.setPosition(0,modal.getPosition().y);
        if(modal.getPosition().x<0)
            modal.setPosition(screen_width,modal.getPosition().y);
}

sf::Vector2f Player::getPos(){
    return modal.getPosition();
}

void Player::draw(){
    window.draw(modal);
}

void Player::reset(){
    modal.setPosition(sf::Vector2f(screen_width/2, screen_length-player_length));
}