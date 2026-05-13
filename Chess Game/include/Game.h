#pragma once
#include "Board.h"
#include "MoveValidator.h"
#include "Player.h"


class Game {
private:
    Board board_;
    Player& white_;
    Player& black_;
    Color currentTurn_;
    GameResult result_;
    int halfMoveCount_;

    void displayStatus() const;
    void switchTurn();

    Player& currentPlayer();
    Player& opponent();

    bool processTurn();
    bool executeMove(string input);
    GameResult handleDrawOffer();

    void applyResult(GameResult r);
    void announceResult() const;
public:
    Game(Player& white, Player& black);
    GameResult start(); 

};
