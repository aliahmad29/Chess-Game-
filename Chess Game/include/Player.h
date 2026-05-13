#pragma once
#include <string>
#include "FileHandler.h" 

using namespace std;


class Player {
private:
    string name_;    
    double score_;   
    int wins_;      
    int losses_;     
    int draws_;      

public:
   
    Player(string name);

  
    string getName() const
    { return name_; }

    double getScore() const
    { return score_; }
    
    int getWins() const
    { return wins_; }
    
    int getLosses() const 
    { return losses_; }
    
    int getDraws() const
    { return draws_; }

   
    void addWin();

   
    void addLoss();

    
    void addDraw();

   
    void displayStats() const;

    
    PlayerRecord toRecord() const;

    
    void saveStats(const string& filepath = "players.dat") const;
};

