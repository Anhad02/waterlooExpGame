#include "headers/Food.h"
#include "./headers/Score.h"
#include "./headers/Player.h"
#include "headers/Global.h"

Food::Food(){
    food=sf::CircleShape(10.0);
    food.setFillColor(sf::Color::Green);
    food.setOutlineThickness(4.0);
    food.setPosition(dist(rd)%(screen_width-100)+50,dist(rd)%(screen_length-100)+50);
    is_visible_food=true;
}

sf::CircleShape Food::getFood(){
    return food;
}

void Food::foodSpawn(Player &player, Score &score){
      //Food Functionality
        if(food.getGlobalBounds().intersects(player.getPlayer().getGlobalBounds()) || !is_visible_food){
            if(is_visible_food){
                score.scoreIncrement();
                food_timer=100;
                food.setPosition(screen_length*2,screen_width*2);
                is_visible_food=false;
            }
                if(score.getScore()==1){
                    game_state=-1;
                }
                if(food_timer<=0){
                    food.setPosition(dist(rd)%(screen_width-100)+50,dist(rd)%(screen_length-100)+50);
                    is_visible_food=true;
                }
            }
}

void Food::decrementTimer(){
    food_timer-=0.05;
}

void Food::draw(){
    window.draw(food);
    decrementTimer();
}

void Food::reset(){
    food.setPosition(dist(rd)%(screen_width-100)+50,dist(rd)%(screen_length-100)+50);
}