#include "headers/Courses.h"
#include "headers/Global.h"
#include "./headers/Player.h"


Courses::Courses(){
    enemies_size = 4;
    for (int i = 0; i < enemies_size; i++)
    {
        sf::RectangleShape enemy(sf::Vector2f(50, 50));
        enemy.setFillColor(sf::Color::Red);
        enemy.setPosition(sf::Vector2f(dist(rd)%(screen_width/enemies_size-80) +(screen_width/enemies_size*i), 30));
        enemy.setOutlineColor(sf::Color::White);
        enemy.setOutlineThickness(3.0);
        enemies.push_back(enemy);
        enemy_speed.push_back(sf::Vector2f(dist(rd)%10/1000.0 *(i<=1 ? 1 : -1),(dist(rd)%11)/200.0+0.025));
    }
}

void Courses::movement(Player &player){
    for (int i = 0; i < enemies_size; i++)
        {
            enemies[i].move(enemy_speed[i]*dt);
            if(enemies[i].getPosition().y>=screen_length){
                enemies[i].setPosition(dist(rd)%(screen_width/enemies_size-player.getWidth()) +(screen_width/enemies_size*i),-80);
            }
            if(enemies[i].getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())){
                previous_state=game_state;
                game_state=0;
            }
        }
}

void Courses::draw(){
    for (auto &enemy:enemies){
            window.draw(enemy);
        }
}

void Courses::reset(){
    for (int i = 0; i < enemies_size; i++){
        enemies[i].setPosition(sf::Vector2f(dist(rd)%(screen_width/enemies_size-80) +(screen_width/enemies_size*i), 30));
    }
     
}