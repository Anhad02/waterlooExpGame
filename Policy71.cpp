#include "headers/Policy71.h"
#include "headers/Global.h"
#include "./headers/Player.h"


Policy71::Policy71(){
    bullet= sf::CircleShape(20.0,10);
    bullet.setFillColor(sf::Color(128, 128, 128));
    bullet.setPosition(0.9*screen_width,50);
    enemy_speed=0.15;
    bullet_time=0.9*screen_width;
}

void Policy71::movement(Player &player){
    if(bullet_time<=-screen_width){
            bullet_time= 720.0;
        }
        sf::Vector2f player_pos=player.getPlayer().getPosition();
        
        float slope,constant;
        if(bullet_time==.9*screen_width){
            bullet.setPosition(bullet_time,50);
            sf::Vector2f bullet_pos=bullet.getPosition();
            slope=(player_pos.y-bullet_pos.y)/(player_pos.x-bullet_pos.x);
            constant=bullet_pos.y-(slope*bullet_pos.x);
            if(player_pos.x<screen_width/3){
                enemy_speed=0.2;
            }
            else if(player_pos.x<2*screen_width/3){
                enemy_speed=0.15;
            }
            else if(player_pos.x<19*screen_width/25){
                enemy_speed=0.075;
            }
            else{
                enemy_speed=0.02;
            }
        }
        bullet.setPosition(bullet_time,slope*bullet_time+constant);
        if(bullet.getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())){
                game_state=0;
            }
}

void Policy71::draw(){
    window.draw(bullet);
}

void Policy71::decrementTimer(){
    bullet_time-=enemy_speed;
}

void Policy71::reset(){
    enemy_speed=0.15;
    bullet_time=screen_width*5;
}

