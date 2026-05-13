#include "../include/Tournament.h"
#include <iostream>


Tournament::Tournament(string name1, string name2, string name3) 
    : players_{ Player(name1), Player(name2), Player(name3) } 
{
}

void Tournament::playMatch(int whiteIdx, int blackIdx, int matchNum) {
    cout << "\n============================================\n";
    cout << "TOURNAMENT MATCH " << matchNum << " / 3\n";
    cout << players_[whiteIdx].getName() << " (White) vs " << players_[blackIdx].getName() << " (Black)\n";
    cout << "============================================\n";

    Game match(players_[whiteIdx], players_[blackIdx]);
    
    match.start(); 
    
    cout << "\nMatch complete. Press ENTER to continue...";
    string dummy;
    getline(cin, dummy);
}

void Tournament::displayStandings() const {
    cout << "\n============================================\n";
    cout << "           TOURNAMENT STANDINGS             \n";
    cout << "============================================\n";
    
    
    for (int i = 0; i < 3; i++) {
        players_[i].displayStats();
    }
    
    cout << "============================================\n\n";
}

int Tournament::getWinnerIndex() const {
    int bestIdx = 0;
    bool isTie = false;

    
    for (int i = 1; i < 3; i++) {
        if (players_[i].getScore() > players_[bestIdx].getScore()) {
            bestIdx = i;       
            isTie = false;     
        } else if (players_[i].getScore() == players_[bestIdx].getScore()) {
            isTie = true;      
        }
    }

    return isTie ? -1 : bestIdx;
}

void Tournament::saveAllResults() const {
    cout << "[Tournament] Saving global rankings for all participants...\n";
    for (int i = 0; i < 3; i++) {
        players_[i].saveStats(); 
    }
}

void Tournament::start() {
    cout << "\nStarting 3-Player Round-Robin Tournament!\n";
    
    
    playMatch(0, 1, 1);
    playMatch(1, 2, 2);
    playMatch(2, 0, 3);

    displayStandings();

    int winnerIdx = getWinnerIndex();
    
    cout << "============================================\n";
    if (winnerIdx == -1) {
        cout << "The tournament ended in a TIE!\n";
    } else {
        cout << "TOURNAMENT CHAMPION: " << players_[winnerIdx].getName() << "!\n";
    }
    cout << "============================================\n";

   
    saveAllResults();
}
