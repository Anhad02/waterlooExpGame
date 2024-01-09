#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
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
void startGame(int x,int y);
void menu();
void gameOver();
void resetGame();
void playAgain(int x,int y);
void loadHighScores(std::vector<LevelHighScore>& highScores);
void saveHighScores(std::vector<LevelHighScore>& highScores);


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

//Game Over
Title game_over_text("THE UW EXPERIENCE",150.0);
Title main_menu("MAIN MENU",325.0);
Title play_again("PLAY AGAIN",400.0);

//dt=0.00021

int main()
{
    window.setFramerateLimit(10);
    LevelHighScore temp={1,0};
    highScores.push_back(temp);
    highScores.push_back(temp);
    highScores.push_back(temp);
    loadHighScores(highScores);
    while (window.isOpen())
    {
        dt=gameClock.restart().asSeconds() * multiplier;
        window.clear(sf::Color(15,15,15));
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    saveHighScores(highScores);
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(game_state==-1){
                        startGame(event.mouseButton.x, event.mouseButton.y);
                    }
                    else if(game_state==0){
                        playAgain(event.mouseButton.x, event.mouseButton.y);
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
            gameOver();
            break;
        }

        window.display();
    }

    return 0;
}

void gameloop(int level)
{
    player.movement();
    player.draw();
    food.foodSpawn(player, score);
    food.draw();
    score.draw();
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
void gameOver(){
    sf::RectangleShape bg(sf::Vector2f(screen_width, screen_length));
    bg.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(bg);
    game_over_text.draw();
    play_again.draw();
    main_menu.draw();
    Title HS("Highscore: "+ to_string(score.getHighScore()),75);
    HS.draw();
}

void startGame(int x,int y){
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
    resetGame();
}

void resetGame(){
    player.reset();
    courses.reset();
    psych.reset();
    bullet.reset();
    food.reset();
    score.reset();
    gameClock.restart();
}

void playAgain(int x,int y){
    if(play_again.mouseClicked(x,y)){
        resetGame();
        game_state=previous_state;
    }
    else if(main_menu.mouseClicked(x,y)){
        game_state=-1;
    }
}

void loadHighScores(std::vector<LevelHighScore>& highScores) {
    std::ifstream ifs("highscores.dat", std::ios::binary);
    if (ifs.is_open()) {
        ifs.read(reinterpret_cast<char*>(highScores.data()), sizeof(LevelHighScore) * highScores.size());
        ifs.close();
    } else {
        std::cerr << "Error loading high scores\n";
    }
}

void saveHighScores(std::vector<LevelHighScore>& highScores) {
    std::ofstream ofs("highscores.dat", std::ios::binary);
    if (ofs.is_open()) {
        ofs.write(reinterpret_cast<const char*>(highScores.data()), sizeof(LevelHighScore) * highScores.size());
        ofs.close();
    } else {
        std::cerr << "Error saving high scores\n";
    }
}
