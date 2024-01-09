#include "headers/Policy71.h"
#include "headers/Global.h"
#include "./headers/Player.h"
#include <iostream>
#include <cmath>



Policy71::Policy71(){
    sf::FloatRect bulletBounds=bullet.getLocalBounds();
    bullet.setOrigin(bulletBounds.left + bulletBounds.width/2.0,bulletBounds.top+bulletBounds.height/2.0);
    bullet.setPosition(screen_width,0);
    enemy_speed=0.075;
    for(int i=1;i<=4;i++){
        if (!bullet_texture[i-1].loadFromFile("./Textures/chakri"+std::to_string(i)+".png")) {
            std::cerr<<"Texture not loaded";
        }
    }
    bullet.scale(0.2,0.2f);
    bullet.setTexture(bullet_texture[0]);
    animationFrames=0.0;
}

void Policy71::movement(Player &player){
    animationFrames+=0.002*dt;
    bullet.setTexture(bullet_texture[(int)floor(animationFrames)]);
    if(animationFrames>=4){
        animationFrames=0;
    }
    if(bullet.getPosition().y>=(screen_length)){
        bullet.setPosition(screen_width,0);
    }
    if(bullet.getPosition().x==(screen_width)){
        calculateConstants(player);
    }
    bullet.move(moved_distance);
    if(bullet.getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())){
                previous_state=game_state;
                game_state=0;
    }
}

void Policy71::draw(){
    window.draw(bullet);
}

void Policy71::reset(){
    bullet.setPosition(screen_width,0);
}

void Policy71::calculateConstants(Player &player){
    direction = player.getPos() - bullet.getPosition();
    length=std::sqrt(direction.x*direction.x +direction.y*direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    moved_distance=normalizedDirection*dt*enemy_speed;
}
