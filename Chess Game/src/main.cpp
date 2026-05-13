#include "include/Game.h"
#include "include/Tournament.h"
#include "include/FileHandler.h"
#include <iostream>



void printMenu() 
{
    cout << "\n======================================\n";
    cout << "       CHESS SIMULATOR C++            \n";
    cout << "======================================\n";
    cout << "1. Two-Player Match\n";
    cout << "2. Three-Player Tournament\n";
    cout << "3. View Global Leaderboard\n"; 
    cout << "4. Exit\n";
    cout << "======================================\n";
    cout << "Choose an option: ";
}


void playTwoPlayerMode()
{
    string p1, p2;
    cout << "Enter Player 1 (White) name: ";
    getline(cin, p1);
    cout << "Enter Player 2 (Black) name: ";
    getline(cin, p2);

    
    Player white(p1);
    Player black(p2);

  
    Game game(white, black);
    game.start();
    
   
    cout << "\nUpdating global rankings...\n";
    white.saveStats();
    black.saveStats();

    cout << "\nPress ENTER to return to menu...";
    string dummy;
    getline(cin, dummy);
}


void playTournamentMode() 
{
    string p1, p2, p3;
    cout << "Enter Player 1 name: ";
    getline(cin, p1);
    cout << "Enter Player 2 name: ";
    getline(cin, p2);
    cout << "Enter Player 3 name: ";
    getline(cin, p3);

   
    Tournament tourney(p1, p2, p3);
    tourney.start();
    


    cout << "\nPress ENTER to return to menu...";
    string dummy;
    getline(cin, dummy);
}

int main() {
    bool running = true;
    
    while (running)
    {
        printMenu();
        string choiceStr;
        getline(cin, choiceStr);
        
        if (choiceStr.empty()) continue;
        
        
        int choice = choiceStr[0] - '0'; 

        switch (choice) {
            case 1:
                playTwoPlayerMode();
                break;
            case 2:
                playTournamentMode();
                break;
            case 3:
                
                FileHandler::displayLeaderboard();
                cout << "Press ENTER to return to menu...";
                getline(cin, choiceStr);
                break;
            case 4:
                cout << "Exiting... Thank you for playing!\n";
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again (1-4).\n";
                break;
        }
    }
    return 0;
}
