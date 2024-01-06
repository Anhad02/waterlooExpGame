#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>


class Score{
    private:
    sf::Text score_text;
    public:
    Score();
    int score;
    int getScore();
    void reset();
    void scoreIncrement();
    sf::Text getScoreText();
    void draw();
    int getHighScore();
};

#endif
