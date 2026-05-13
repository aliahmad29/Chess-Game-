#pragma once
#include "Player.h"
#include "Game.h"


class Tournament {
private:
    Player players_[3]; 


    void playMatch(int whiteIdx, int blackIdx, int matchNum);


    void displayStandings() const;


    int getWinnerIndex() const;
public:
   
    Tournament(string name1, string name2, string name3);

    
    void start();

    
    void saveAllResults() const;

};
