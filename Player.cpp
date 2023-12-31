#include "./headers/Player.h"
#include "./headers/Global.h"

Player::Player(){
    player_width=80.0;
    player_length=80.0;
    modal=sf::RectangleShape(sf::Vector2f(player_width, player_length));
    modal.setFillColor(sf::Color::Blue);
    modal.setPosition(sf::Vector2f((screen_width-player_width)/2, screen_length-1.5*player_length));
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
            modal.move(sf::Vector2f(-0.08, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            modal.move(sf::Vector2f(0.08, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& modal.getPosition().y<=screen_length-player_length)
            modal.move(sf::Vector2f(0, 0.08));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && modal.getPosition().y>=0)
            modal.move(sf::Vector2f(0, -0.08));
        //Player goes out of bonds 
        if(modal.getPosition().x>(screen_width-player_width))
            modal.setPosition(-player_width,modal.getPosition().y);
        // if(player.getPosition().y>(screen_length-player_length))
        //     player.setPosition(player.getPosition().x,-player_length);
        if(modal.getPosition().x<(-player_width))
            modal.setPosition(screen_width-player_width,modal.getPosition().y);
        // if(player.getPosition().y<(-player_length))
        //     player.setPosition(player.getPosition().x,screen_length-player_length);
}

void Player::draw(){
    window.draw(modal);
}

void Player::reset(){
    modal.setPosition(sf::Vector2f((screen_width-player_width)/2, screen_length-1.5*player_length));
}