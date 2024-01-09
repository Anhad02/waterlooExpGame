#include "headers/Courses.h"
#include "headers/Global.h"
#include "./headers/Player.h"
#include <iostream>


Courses::Courses(){
    enemies_size = 4;
    for (int i = 0; i < enemies_size; i++)
    {
        sf::Sprite enemy;
        if (!course_texture.loadFromFile("./Textures/scroll.png")) {
            std::cerr<<"Texture not loaded";
        }
        enemy.setTexture(course_texture);
        enemy.setScale(0.1f,0.1f);
        float spriteWidth = static_cast<float>(texture.getSize().x);
        float spriteHeight = static_cast<float>(texture.getSize().y);
        enemy.setOrigin(spriteWidth / 2.0f, spriteHeight / 2.0f);
        enemy.setPosition(sf::Vector2f(dist(rd)%(screen_width/enemies_size-80)+(screen_width/enemies_size*i), -80));
        enemies.push_back(enemy);
        enemy_speed.push_back(sf::Vector2f(dist(rd)%10/1000.0 *(i<=1 ? 1 : -1),(dist(rd)%11)/200.0+0.025));
        sf::Text course_name;
        course_name.setFont(font);
        course_name.setCharacterSize(20);
        course_name.setColor(sf::Color::Red);
        course_name.setPosition(enemy.getPosition());
        enemy_text.push_back(course_name);
    }
}

void Courses::movement(Player &player){
    for (int i = 0; i < enemies_size; i++)
        {
            enemies[i].move(enemy_speed[i]*dt);
            enemy_text[i].setPosition(enemies[i].getPosition());
            if(enemies[i].getPosition().y>=screen_length){
                enemies[i].setPosition(dist(rd)%(screen_width/enemies_size-player.getWidth()) +(screen_width/enemies_size*i),-80);
                int randomIndex = std::rand() % (sizeof(Eng) / sizeof(Eng[0]));
                if(game_state==1)
                enemy_text[i].setString(Arts[randomIndex]);
                else if(game_state==2)
                enemy_text[i].setString(Math[randomIndex]);
                else if(game_state==3)
                enemy_text[i].setString(Eng[randomIndex]);

            }
            if(enemies[i].getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())){
                previous_state=game_state;
                game_state=0;
            }
        }
}

void Courses::draw(){
    for (int i=0;i<enemies.size();i++){
            window.draw(enemies[i]);
            window.draw(enemy_text[i]);
        }
}

void Courses::reset(){
    change_type(game_state);
    for (int i = 0; i < enemies_size; i++){
        enemies[i].setPosition(sf::Vector2f(dist(rd)%(screen_width/enemies_size-80) +(screen_width/enemies_size*i), -200));
    }
}

void Courses::change_type(int level){

    if(level==1){
        for(auto &course_names:enemy_text){
            int randomIndex = std::rand() % (sizeof(Arts) / sizeof(Arts[0]));
            course_names.setString(Arts[randomIndex]);
        }
    }
    else if(level==2){
        for(auto &course_names:enemy_text){
            int randomIndex = std::rand() % (sizeof(Math) / sizeof(Math[0]));
            course_names.setString(Math[randomIndex]);
        }

    }
    else if(level==3){
        for(auto &course_names:enemy_text){
            int randomIndex = std::rand() % (sizeof(Eng) / sizeof(Eng[0]));
            course_names.setString(Eng[randomIndex]);
        }
    }

}