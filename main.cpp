#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include "./headers/Player.h"
#include "./headers/Global.h"
#include "./headers/Food.h"
#include "./headers/Score.h"
#include "./headers/Courses.h"
#include "./headers/Psych.h"
#include "./headers/Policy71.h"
#include "./headers/Title.h"


using namespace std;

void gameloop(int level);
void menu();
void startGame(int x,int y);
void resetGame();

// Player
Player player;

// Courses
Courses courses;

// Enemy 2
Psych psych;

// Enemy 3
Policy71 bullet;

// Food
Food food;

// Score
Score score;

//Menu
Title header("THE UW EXPERIENCE",50.0);
Title lvl1("LEVEL 1: ARTS",150.0);
Title lvl2("LEVEL 2: MATH",225.0);
Title lvl3("LEVEL 3: ENGINEERING",300.0);
Title endless("ENDLESS MODE",375.0);


int main()
{
    while (window.isOpen())
    {
        window.clear(sf::Color(150, 250, 255));
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(game_state==-1){
    
                    startGame(event.mouseButton.x, event.mouseButton.y); 
                    }
                    break;
            }
          
        }

        switch (game_state)
        {
        case MENU:
            menu();
            break;
        case ARTS:
            gameloop(ARTS);
            break;
        case MATH:
            gameloop(MATH);
            break;
        case ENG:
            gameloop(ENG);
            break;
        case ENDLESS:
            gameloop(ENDLESS);
            break;
        case GAME_OVER:
            break;
        }

        // if (game_over)
        // {
        //     sf::RectangleShape bg(sf::Vector2f(screen_width, screen_length));
        //     bg.setFillColor(sf::Color(0, 0, 0, 100));
        //     window.draw(bg);
        // }

        window.display();

        // Time
        bullet.decrementTimer();
    }

    return 0;
}

void gameloop(int level)
{
    player.movement();
    player.draw();
    food.foodSpawn(player, score);
    food.draw();
    if (level >= 1)
    {
        courses.movement(player);
        courses.draw();
    }
    if (level >= 2)
    {
        psych.movement(player);
        psych.draw();
    }
    if (level >= 3)
    {
        bullet.movement(player);
        bullet.draw();
    }
}

void menu(){
    header.draw();
    lvl1.draw();
    lvl2.draw();
    lvl3.draw();
    endless.draw();
}

void startGame(int x,int y){
    resetGame();
    if(lvl1.mouseClicked(x,y)){
        game_state=1;
    }
    else if(lvl2.mouseClicked(x,y)){
        game_state=2;
    }
    else if(lvl3.mouseClicked(x,y)){
        game_state=3;
    }
    else if(endless.mouseClicked(x,y)){
        game_state=4;
    }
}

void resetGame(){
    player.reset();
    courses.reset();
    psych.reset();
    bullet.reset();
    food.reset();
    score.reset();
}
