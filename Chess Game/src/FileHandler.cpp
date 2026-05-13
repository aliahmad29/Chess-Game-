#include "../include/FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>


void FileHandler::writeAll(const vector<PlayerRecord>& records, const string& filepath) {
    
    ofstream file(filepath, ios::trunc);
    
    if (!file.is_open()) {
        cerr << "[FileHandler] Critical Error: Unable to open " << filepath << " for writing.\n";
        return;
    }

    
    for (const auto& r : records) {
        file << r.name   << ","
             << r.score  << ","
             << r.wins   << ","
             << r.losses << ","
             << r.draws  << "\n";
    }
    
    file.close();
}

vector<PlayerRecord> FileHandler::loadAllPlayers(const string& filepath) {
    vector<PlayerRecord> records;
    ifstream file(filepath);

    
    if (!file.is_open()) {
        return records;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; 

        
        istringstream ss(line);
        string token;
        PlayerRecord rec;

        try {
            
            getline(ss, rec.name, ',');
            
            
            getline(ss, token, ','); rec.score  = stod(token);
            getline(ss, token, ','); rec.wins   = stoi(token);
            getline(ss, token, ','); rec.losses = stoi(token);
            getline(ss, token, ','); rec.draws  = stoi(token);
            
            records.push_back(rec);
        } catch (...) {
           
            cerr << "[FileHandler] Warning: Skipping corrupted data line in " << filepath << "\n";
        }
    }
    
    file.close();
    return records;
}

void FileHandler::savePlayer(const PlayerRecord& record, const string& filepath) {
    
    vector<PlayerRecord> records = loadAllPlayers(filepath);

    
    bool found = false;
    for (auto& r : records) {
        if (r.name == record.name) {
            
            r.score  += record.score;
            r.wins   += record.wins;
            r.losses += record.losses;
            r.draws  += record.draws;
            found = true;
            break;
        }
    }

    
    if (!found) {
        records.push_back(record);
    }

   
    writeAll(records, filepath);
}

void FileHandler::displayLeaderboard(const string& filepath) {
    vector<PlayerRecord> records = loadAllPlayers(filepath);

    if (records.empty()) {
        cout << "\n>>> The Hall of Fame is empty! Play some matches to record history. <<<\n\n";
        return;
    }

 
    sort(records.begin(), records.end(), [](const PlayerRecord& a, const PlayerRecord& b) {
        if (a.score != b.score) return a.score > b.score; 
        return a.wins > b.wins; 
    });

    
    cout << "\n============================================================\n";
    cout << "                GLOBAL CHESS LEADERBOARD                    \n";
    cout << "============================================================\n";
    cout << left
         << setw(5)  << "Rank"
         << setw(18) << "Player Name"
         << setw(10) << "Total Pts"
         << setw(8)  << "Wins"
         << setw(8)  << "Losses"
         << setw(8)  << "Draws"
         << "\n";
    cout << "------------------------------------------------------------\n";

    int rank = 1;
    for (const auto& r : records) {
        cout << left
             << setw(5)  << (to_string(rank++) + ".")
             << setw(18) << r.name
             << setw(10) << fixed << setprecision(1) << r.score
             << setw(8)  << r.wins
             << setw(8)  << r.losses
             << setw(8)  << r.draws
             << "\n";
    }
    cout << "============================================================\n\n";
}
