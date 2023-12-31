#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>
#include <random>

#define GAME_OVER 0
#define ARTS 1
#define MATH 2
#define ENG 3
#define ENDLESS 4
#define MENU -1

inline int screen_width=800;
inline int screen_length=500;
inline sf::RenderWindow window(sf::VideoMode(screen_width, screen_length), "Dodger Game");
inline std::random_device rd;
inline std::uniform_int_distribution<int> dist;
inline int game_state=-1;
inline sf::Font font;


#endif