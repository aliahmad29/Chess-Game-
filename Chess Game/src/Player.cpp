#include "../include/Player.h"
#include <iostream>



Player::Player(string name) {
    name_ = name;
    score_ = 0.0;
    wins_ = 0;
    losses_ = 0;
    draws_ = 0;
}

void Player::addWin() {
    wins_++;
    score_ += 1.0; 
}

void Player::addLoss() {
    losses_++; 
}

void Player::addDraw() {
    draws_++;
    score_ += 0.5; 
}

void Player::displayStats() const {
    
    cout << "Player: " << name_ 
         << " | Score: " << score_ 
         << " | Wins: " << wins_ 
         << " | Losses: " << losses_ 
         << " | Draws: " << draws_ << "\n";
}

PlayerRecord Player::toRecord() const {
    
    PlayerRecord rec;
    rec.name   = name_;
    rec.score  = score_;
    rec.wins   = wins_;
    rec.losses = losses_;
    rec.draws  = draws_;
    return rec;
}

void Player::saveStats(const string& filepath) const {
   
    FileHandler::savePlayer(this->toRecord(), filepath);
}
