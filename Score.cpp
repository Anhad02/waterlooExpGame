#include "headers/Score.h"

Score::Score(){
    score=0;
}

void Score::reset(){
    score=0;
}

void Score::scoreIncrement(){
    score++;
}

int Score::getScore(){
    return score;
}