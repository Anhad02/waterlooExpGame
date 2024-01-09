#include "./headers/Player.h"
#include "./headers/Global.h"
#include <iostream>

Player::Player(){
    if (!texture.loadFromFile("./Textures/Character.png")) {
        std::cerr<<"Texture not loaded";
    }
    modal.setTexture(texture);
    modal.setTextureRect(sf::IntRect(0,0,60,96));
    sf::FloatRect modalBounds=modal.getLocalBounds();
    modal.setOrigin(modalBounds.left + modalBounds.width/2.0,modalBounds.top+modalBounds.height/2.0);
    modal.setPosition(sf::Vector2f(screen_width/2, screen_length-player_length));
    player_width=modalBounds.width;
    player_length=modalBounds.height;
    animationFrames=0;
}

sf::Sprite Player::getPlayer() {
    return modal;
}

int Player::getWidth() {
    return player_width;
}

int Player::getLength() {
    return player_length;
}

void Player::movement() {
    animationFrames+=0.08*dt;
    if(animationFrames>=256){
        animationFrames=0;
    }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            modal.move(sf::Vector2f(-0.06 * dt, 0));
            modal.setTextureRect(sf::IntRect((floor(animationFrames/txt_width))*txt_width,txt_length*2,txt_width,txt_length));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            modal.move(sf::Vector2f(0.06 * dt, 0));
            modal.setTextureRect(sf::IntRect((floor(animationFrames/txt_width))*txt_width,txt_length*3,txt_width,txt_length));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& modal.getPosition().y<=screen_length-player_length/2){
            modal.move(sf::Vector2f(0, 0.06 * dt));
            modal.setTextureRect(sf::IntRect((floor(animationFrames/txt_width))*txt_width,0,txt_width,txt_length));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && modal.getPosition().y>=0+player_length/2){
            modal.move(sf::Vector2f(0, -0.06 * dt));
            modal.setTextureRect(sf::IntRect((floor(animationFrames/txt_width))*txt_width,txt_length,txt_width,txt_length));
        }
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