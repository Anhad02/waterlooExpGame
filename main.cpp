#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <math.h>
#include <filesystem>

#include "./headers/Player.h"
#include "./headers/Global.h"
#include "./headers/Food.h"
#include "./headers/Score.h"
#include "./headers/Courses.h"
#include "./headers/Psych.h"
#include "./headers/Policy71.h"
#include "./headers/Title.h"
#include "./headers/ControlSprite.h"

using namespace std;

void gameloop(int level);
void startGame(int x, int y);
void menu();
void gameOver();
void resetGame();
void playAgain(int x, int y);
void loadHighScores(std::vector<LevelHighScore> &highScores);
void saveHighScores(std::vector<LevelHighScore> &highScores);
void set_summary();
void controlsNavigation(int x, int y);
void displayControls();

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

// Controls
Title movement("Movement", 30);
Title goal("GOAL", 30);
Title goaltext("Consume        to surive your degree \n \n \n Collect enough       to Graduate", 70);
ControlSprite control_sprite;

bool flag = true;

// Menu
Title header("THE UW EXPERIENCE", 50.0);
Title lvl1("LEVEL 1: ARTS", 150.0);
Title lvl2("LEVEL 2: MATH", 225.0);
Title lvl3("LEVEL 3: ENGINEERING", 300.0);
Title controls("CONTROLS", 375.0);

// Game Over
Title game_over_text("YOU FAILED!!!", 150.0);
Title summary("", 250);
Title main_menu("MAIN MENU", 365.0);
Title play_again("PLAY AGAIN", 440.0);
Title esc("[Esc]", 365.0);
Title enter("[Enter]", 440.0);

// Background
sf::Sprite space_bg;

// dt=0.00021

int main()
{
    filesystem::path currentPath = std::filesystem::current_path();
    // Display the current working directory
    std::cout << "Current Working Directory: " << currentPath << std::endl;

    window.setFramerateLimit(500);
    main_song.openFromFile("./Sounds/Megalovania.ogg");
    main_song.setLoop(true);
    bg.loadFromFile("./Textures/blackspace.png");
    space_bg.setTexture(bg);
    space_bg.scale(1.55, 1.38);
    LevelHighScore temp = {1, 0};
    highScores.push_back(temp);
    highScores.push_back(temp);
    highScores.push_back(temp);
    loadHighScores(highScores);
    while (window.isOpen())
    {
        dt = gameClock.restart().asSeconds() * multiplier;
        window.clear(sf::Color(15, 15, 15));
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                saveHighScores(highScores);
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (game_state == 0)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        resetGame();
                        game_state = previous_state;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        game_state = -1;
                    }
                }
            case sf::Event::MouseButtonPressed:
                if (game_state == -1)
                {
                    startGame(event.mouseButton.x, event.mouseButton.y);
                }
                else if (game_state == 0)
                {
                    playAgain(event.mouseButton.x, event.mouseButton.y);
                }
                else if (game_state == 4)
                {
                    controlsNavigation(event.mouseButton.x, event.mouseButton.y);
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
        case CONTROLS:
            displayControls();
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
    if (main_song.getStatus() != sf::Music::Playing)
    {
        main_song.play();
    }
    window.draw(space_bg);
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
    player.movement();
    player.draw();
}

void menu()
{
    window.draw(space_bg);
    header.draw();
    lvl1.draw();
    lvl2.draw();
    lvl3.draw();
    controls.draw();
}
void gameOver()
{
    window.draw(space_bg);
    player.draw();
    if (previous_state >= 1)
    {
        courses.draw();
    }
    if (previous_state >= 2)
    {
        psych.draw();
    }
    if (previous_state >= 3)
    {
        bullet.draw();
    }
    sf::RectangleShape bg(sf::Vector2f(screen_width, screen_length));
    bg.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(bg);
    set_summary();
    if (score.getScore() > 20)
    {
        deathcase = 4;
    }
    game_over_text.draw();
    play_again.draw();
    main_menu.draw();
    esc.setCharSize(20);
    esc.centerText();
    esc.setPosition(570, 365);
    enter.setCharSize(20);
    enter.centerText();
    enter.setPosition(580, 440);
    enter.draw();
    esc.draw();
    Title HS("Highscore: " + to_string(score.getHighScore()), 75);
    HS.draw();
}

void startGame(int x, int y)
{
    if (lvl1.mouseClicked(x, y))
    {
        game_state = 1;
    }
    else if (lvl2.mouseClicked(x, y))
    {
        game_state = 2;
    }
    else if (lvl3.mouseClicked(x, y))
    {
        game_state = 3;
    }
    else if (controls.mouseClicked(x, y))
    {
        game_state = 4;
    }
    resetGame();
}

void resetGame()
{
    flag = true;
    player.reset();
    courses.reset();
    psych.reset();
    bullet.reset();
    food.reset();
    score.reset();
    gameClock.restart();
}

void playAgain(int x, int y)
{
    if (play_again.mouseClicked(x, y))
    {
        resetGame();
        game_state = previous_state;
    }
    else if (main_menu.mouseClicked(x, y))
    {
        game_state = -1;
    }
}

void controlsNavigation(int x, int y)
{
    if (main_menu.mouseClicked(x, y))
    {
        game_state = -1;
    }
}

void set_summary()
{
    summary.setCharSize(20);
    switch (deathcase)
    {
    case 1:
        if (flag)
        {
            int temp = dist(rd) % 3;
            if (temp == 0)
                summary.setText("Did you just fail a another course! You should probably shift to Laurier smh");
            else if (temp == 1)
                summary.setText("Oh! You failed a course. Maybe go protest with the students from Algoma");
            else
                summary.setText("What did you think would happen smoking so much weed. You failed the term");
            flag = false;
        }
        break;
    case 2:
        if (flag)
        {
            int temp = dist(rd) % 3;
            if (temp == 0)
                summary.setText("You had a good run, but depression finally got you. Try again in your next life");
            else if (temp == 1)
                summary.setText("You smoked weed the entire night. Now you're thinking\n about life before Waterloo. Boom now you're depressed.");
            else
                summary.setText("If you think you don't belong here and everybody else is better, you're probably right!");
            flag = false;
        }
        break;
    case 3:
        if (flag)
        {
            if (dist(rd) % 2 == 0)
                summary.setText("Maybe you should leave the cheating to your ex. Atleast they didnt get caught");
            else
                summary.setText("Honesty is the best policy. You can tell your kids \nthat when they ask why you don't have a degree.");
            flag = false;
        }
        break;
    case 4:
        game_over_text.setText("YOU GRADUATED!!");
        game_over_text.centerText();
        summary.setText("Congratulations,you did it! If only you spent this much effort on your actual degree.");
    }
    summary.centerText();
    summary.draw();
}

void loadHighScores(std::vector<LevelHighScore> &highScores)
{
    std::ifstream ifs("highscores.dat", std::ios::binary);
    if (ifs.is_open())
    {
        ifs.read(reinterpret_cast<char *>(highScores.data()), sizeof(LevelHighScore) * highScores.size());
        ifs.close();
    }
    else
    {
        std::cerr << "Error loading high scores\n";
    }
}

void saveHighScores(std::vector<LevelHighScore> &highScores)
{
    std::ofstream ofs("highscores.dat", std::ios::binary);
    if (ofs.is_open())
    {
        ofs.write(reinterpret_cast<const char *>(highScores.data()), sizeof(LevelHighScore) * highScores.size());
        ofs.close();
    }
    else
    {
        std::cerr << "Error saving high scores\n";
    }
}

void displayControls()
{
    window.draw(space_bg);
    control_sprite.draw();
    movement.setPosition(200, 20);
    movement.draw();
    goal.setPosition(600, 20);
    goal.draw();
    goaltext.setCharSize(23);
    goaltext.centerText();
    goaltext.setPosition(600, 150);
    goaltext.draw();
    food.setPosition(515, 140);
    food.draw();
    food.setPosition(575, 215);
    food.draw();
    main_menu.draw();
}