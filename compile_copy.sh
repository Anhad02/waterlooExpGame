#!/bin/bash

g++ hi.cpp -I /opt/homebrew/Cellar/sfml/2.6.1/include -o help -L /opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

./help