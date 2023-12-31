#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>


class Score{
    public:
    Score();
    int score;
    int getScore();
    void reset();
    void scoreIncrement();
};

#endif
