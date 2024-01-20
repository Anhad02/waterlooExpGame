#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

#define GAME_OVER 0
#define ARTS 1
#define MATH 2
#define ENG 3
#define CONTROLS 4
#define MENU -1

inline int screen_width = 800;
inline int screen_length = 500;
inline sf::RenderWindow window(sf::VideoMode(screen_width, screen_length), "Dodger Game");
inline sf::Clock gameClock;
inline std::random_device rd;
inline std::uniform_int_distribution<int> dist;
inline int game_state = -1;
inline int previous_state = -1;
inline sf::Font font;
inline sf::Font course_font;
inline sf::Texture texture;
inline float txt_width = 252 / 4;
inline float txt_length = 380 / 4;
inline float offset_x = 5;
inline float offset_y = 14;
inline sf::Texture food_texture;
inline sf::Texture course_texture;
inline sf::Texture psych_texture;
inline sf::Texture control_texture;
inline sf::Texture bullet_texture[4];
inline sf::Texture bg;
inline int deathcase;
inline sf::Music death_sound;
inline sf::Music main_song;
inline float dt;
inline float multiplier = 5000.0;
struct LevelHighScore
{
    int level;
    int highScore;
};
inline std::vector<LevelHighScore> highScores;
inline std::string Arts[8] = {
    "ECON\n  101",
    "ECON\n  102",
    "ECON\n  371",
    "AFM\n  101",
    "AFM\n  121",
    "AFM\n  102",
    "BET \n  210",
    "HRM \n  200",
};
inline std::string Math[8] = {
    " CS \n  135",
    "MATH\n  135 ",
    "MATH\n  137",
    "STAT\n  230",
    "STAT\n  334",
    "ECON\n  231",
    " CS \n  136",
    " CS \n  234"};
inline std::string Eng[3] = {
    "SE\n 102",
    "SE\n 111",
    "SE\n 230"};
#endif