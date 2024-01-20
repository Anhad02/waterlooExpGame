#!/bin/bash

g++ -std=c++17 main.cpp Food.cpp Courses.cpp Player.cpp Policy71.cpp Psych.cpp Score.cpp Title.cpp ControlSprite.cpp -I /opt/homebrew/Cellar/sfml/2.6.1/include -o prog -L /opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

./prog