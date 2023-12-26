#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>

using namespace std;

void gameloop();

int screen_width=800;
int screen_length=500;
sf::RenderWindow window(sf::VideoMode(screen_width, screen_length), "Dodger Game");

//Player
int player_width=80;
int player_length=80;
sf::RectangleShape player(sf::Vector2f(player_width, player_length));

// Enemy 1
random_device rd;
uniform_int_distribution<int> dist;
vector<sf::RectangleShape> enemies;
vector<sf::Vector2f> enemy_speed;
int enemies_size = 4;

//Enemy 2
sf::CircleShape psych_enemy(30.0);
float psych_enemy_time= -800.0;

//Enemy 3
sf::CircleShape bullet_enemy(20.0,10);
int score=0;
float bullet_time=screen_width*5;
float speed=0.15;

//Food 
sf::CircleShape food(10.0);
bool is_visible_food=true;
float food_timer;

//Game State
bool game_over=false;

int main()
{
    player.setFillColor(sf::Color::Blue);
    player.setPosition(sf::Vector2f(screen_width/2-player_width/2, screen_length-player_length-40));

    //Enemy 1
    for (int i = 0; i < enemies_size; i++)
    {
        int random=rand();
        sf::RectangleShape enemy(sf::Vector2f(50, 50));
        enemy.setFillColor(sf::Color::Red);
        enemy.setPosition(sf::Vector2f(dist(rd)%(screen_width/enemies_size-player_width) +(screen_width/enemies_size*i), 30));
        enemy.setOutlineColor(sf::Color::White);
        enemy.setOutlineThickness(3.0);
        enemies.push_back(enemy);
        enemy_speed.push_back(sf::Vector2f(dist(rd)%10/1000.0 *(i<=1 ? 1 : -1),(dist(rd)%11)/200.0+0.025));
    }

    //Enemy 2
    psych_enemy.setFillColor(sf::Color(128,0,128));
    psych_enemy.setPosition(0.0,200);

    //Enemy 3
    bullet_enemy.setFillColor(sf::Color(128, 128, 128));
    food.setFillColor(sf::Color::Green);
    food.setPosition(dist(rd)%(screen_width-100)+50,dist(rd)%(screen_length-100)+50);
    food.setOutlineThickness(4.0);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(!game_over){
            gameloop();
        }

        //Drawing
        window.clear(sf::Color(150, 250, 255));
        window.draw(player);
        window.draw(food);
        for (auto &enemy:enemies){
            window.draw(enemy);
        }
        if(psych_enemy_time>-100){
            window.draw(psych_enemy);
        }
        window.draw(bullet_enemy);

        if(game_over){
            sf::RectangleShape bg(sf::Vector2f(screen_width,screen_length));
            bg.setFillColor(sf::Color(0,0,0,100));
            window.draw(bg);
        }
        
        window.display();

        //Time
        psych_enemy_time=psych_enemy_time+0.1;
        bullet_time=bullet_time-speed;
        food_timer=food_timer-0.05;
    }

    return 0;
}

void gameloop()
{
    //Player Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(sf::Vector2f(-0.08, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(sf::Vector2f(0.08, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& player.getPosition().y<=screen_length-player_length)
            player.move(sf::Vector2f(0, 0.08));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y>=0)
            player.move(sf::Vector2f(0, -0.08));
        //Player goes out of bonds 
        if(player.getPosition().x>(screen_width-player_width))
            player.setPosition(-player_width,player.getPosition().y);
        // if(player.getPosition().y>(screen_length-player_length))
        //     player.setPosition(player.getPosition().x,-player_length);
        if(player.getPosition().x<(-player_width))
            player.setPosition(screen_width-player_width,player.getPosition().y);
        // if(player.getPosition().y<(-player_length))
        //     player.setPosition(player.getPosition().x,screen_length-player_length);

        //Food Functionality
        if(food.getGlobalBounds().intersects(player.getGlobalBounds()) || !is_visible_food){
            if(is_visible_food){
                score++;
                food_timer=100;
                food.setPosition(screen_length*2,screen_width*2);
                is_visible_food=false;
            }
                if(score==10){
                    cout<<"You Win";
                    // window.close();
                }
                if(food_timer<=0){
                    food.setPosition(dist(rd)%(screen_width-100)+50,dist(rd)%(screen_length-100)+50);
                    is_visible_food=true;
                }
            }

        //Enemy 1 Functionallity
        for (int i = 0; i < enemies_size; i++)
        {
            enemies[i].move(enemy_speed[i]);
            if(enemies[i].getPosition().y>=500){
                enemies[i].setPosition(dist(rd)%(screen_width/enemies_size-player_width) +(screen_width/enemies_size*i),-80);
            }
            if(enemies[i].getGlobalBounds().intersects(player.getGlobalBounds())){
                game_over=true;
            }
        }

        //Enemy Functionality 2
        if(psych_enemy_time>=screen_width){
            psych_enemy_time= -screen_width;
        }
        psych_enemy.setPosition(psych_enemy_time,200.0+150*sin(psych_enemy_time/65));
        if(psych_enemy.getGlobalBounds().intersects(player.getGlobalBounds())){
                game_over=true;
            }

        //Enemy Functionality 3
        if(bullet_time<=-screen_width){
            bullet_time= 720.0;
        }
        sf::Vector2f player_pos=player.getPosition();
        
        float slope,constant;
        if(bullet_time==.9*screen_width){
            bullet_enemy.setPosition(bullet_time,50);
            sf::Vector2f bullet_pos=bullet_enemy.getPosition();
            slope=(player_pos.y-bullet_pos.y)/(player_pos.x-bullet_pos.x);
            constant=bullet_pos.y-(slope*bullet_pos.x);
            if(player_pos.x<screen_width/3){
                speed=0.2;
            }
            else if(player_pos.x<2*screen_width/3){
                speed=0.15;
            }
            else if(player_pos.x<19*screen_width/25){
                speed=0.075;
            }
            else{
                speed=0.02;
            }
        }
        bullet_enemy.setPosition(bullet_time,slope*bullet_time+constant);
        if(bullet_enemy.getGlobalBounds().intersects(player.getGlobalBounds())){
                game_over=true;
            }

}
