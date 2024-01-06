#include "headers/Score.h"
#include "headers/Global.h"
#include <iostream>


Score::Score(){
    score=0;
    score_text.setString(std::to_string(score));
    score_text.setFont(font);
    score_text.setCharacterSize(50);
    // score_text.setScale(5,5);
    score_text.setPosition(10,0); 
    score_text.setColor(sf::Color::Yellow);
}

void Score::reset(){
    score=0;
    score_text.setString(std::to_string(score));
}

int Score::getScore(){
    return score;
}

void Score::scoreIncrement(){
    score++;
    score_text.setString(std::to_string(score));
    if(game_state==1){
        highScores[0].highScore=std::max(highScores[0].highScore, score);
    }
    else if(game_state==2){
        highScores[1].highScore=std::max(highScores[1].highScore, score);
    }
    else if(game_state==3){
        highScores[2].highScore=std::max(highScores[2].highScore, score);
    }
}

void Score::draw(){
    window.draw(score_text);
}

int Score::getHighScore(){
    if(previous_state==1){
        return highScores[0].highScore;
    }
    else if(previous_state==2){
        return highScores[1].highScore;
    }
    else if(previous_state==3){
        return highScores[2].highScore;
    }
}

sf::Text Score::getScoreText(){
    return score_text;
}

