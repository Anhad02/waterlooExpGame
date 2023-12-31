#include "headers/Psych.h"
#include "headers/Global.h"
#include "./headers/Player.h"


Psych::Psych(){
    psych_enemy.setRadius(30.0);
    psych_enemy.setFillColor(sf::Color(128,0,128));
    psych_enemy.setPosition(-800.0,200);
    enemy_speed=-800.0;
    
}

void Psych::movement(Player &player){
    if(enemy_speed>=screen_width){
            enemy_speed= -screen_width;
        }
        psych_enemy.setPosition(enemy_speed,200.0+150*sin(enemy_speed/65));
        if(psych_enemy.getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())){
                game_state=0;
        }
}

void Psych::draw(){
    window.draw(psych_enemy);
    decrementTimer();
}

void Psych::decrementTimer(){
    enemy_speed+=0.1;
}

void Psych::reset(){
    psych_enemy.setPosition(-800.0,200);
    enemy_speed=-800.0;
}

