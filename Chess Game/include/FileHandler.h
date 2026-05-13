#pragma once
#include <string>
#include <vector>

using namespace std;


struct PlayerRecord {
    string name;   
    double score;   
    int wins;      
    int losses;     
    int draws;      
};


class FileHandler {
private:
    static void writeAll(const vector<PlayerRecord>& records, const string& filepath);

public:
   
    static void savePlayer(const PlayerRecord& record, const string& filepath = "players.dat");

   
    static vector<PlayerRecord> loadAllPlayers(const string& filepath = "players.dat");

    static void displayLeaderboard(const string& filepath = "players.dat");

};
