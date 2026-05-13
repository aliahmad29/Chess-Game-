#include "../include/Game.h"
#include <iostream>

Game::Game(Player& white, Player& black) : white_(white), black_(black) {
    currentTurn_ = Color::WHITE;
    result_ = GameResult::ONGOING;
    halfMoveCount_ = 0;
}

void Game::displayStatus() const {
    board_.display(currentTurn_);
    
    cout << "\nTurn: " << colorName(currentTurn_) << " (" << ((currentTurn_ == Color::WHITE) ? white_.getName() : black_.getName()) << ")\n";
    
    if (MoveValidator::isInCheck(currentTurn_, board_)) {
        cout << "*** CHECK! Your King is in danger! ***\n";
    }
}

void Game::switchTurn() {
    currentTurn_ = opposite(currentTurn_);
    halfMoveCount_++;
}

Player& Game::currentPlayer() {
    if (currentTurn_ == Color::WHITE) {
        return white_;
    } else {
        return black_;
    }
}

Player& Game::opponent() {
    if (currentTurn_ == Color::WHITE) {
        return black_;
    } else {
        return white_;
    }
}

GameResult Game::handleDrawOffer() {
    cout << currentPlayer().getName() << " has offered a draw.\n";
    cout << opponent().getName() << ", do you accept? (y/n): ";
    
    string resp;
    getline(cin, resp);
    
    if (resp == "y" || resp == "Y") {
        return GameResult::DRAW;
    }
    cout << "Draw declined. Game continues.\n";
    return GameResult::ONGOING;
}

bool Game::executeMove(string input) {
    
    if (input == "resign") {
        if (currentTurn_ == Color::WHITE) {
            result_ = GameResult::BLACK_WINS;
        } else {
            result_ = GameResult::WHITE_WINS;
        }
        return true; 
    }
    
    
    if (input == "draw") {
        GameResult r = handleDrawOffer();
        if (r == GameResult::DRAW) {
            result_ = GameResult::DRAW;
            return true; 
        }
        return false; 
    }

    bool isMoveValid = false;
    Move m = MoveValidator::parseInput(input, currentTurn_, board_, isMoveValid);
    
    if (isMoveValid) {
        board_.makeMove(m);
        return true; 
    } else {
        cout << "Invalid move. Please try again.\n";
        return false; 
    }
}

bool Game::processTurn() {
    displayStatus();
    
    bool validTurnCompleted = false;
    
    
    while (!validTurnCompleted) {
        cout << "Enter move (e.g., e2-e4), 'resign', or 'draw': ";
        string input;
        getline(cin, input);
        
        validTurnCompleted = executeMove(input);
        
        if (result_ != GameResult::ONGOING) {
            return true;
        }
    }

    switchTurn();

    
    if (MoveValidator::isCheckmate(currentTurn_, board_)) {
        if (currentTurn_ == Color::WHITE) {
            result_ = GameResult::BLACK_WINS;
        } else {
            result_ = GameResult::WHITE_WINS;
        }
        return true; 
    }
    
    if (MoveValidator::isStalemate(currentTurn_, board_)) {
        result_ = GameResult::DRAW;
        return true; 
    }

    return false; 
}


void Game::applyResult(GameResult r) {
    if (r == GameResult::WHITE_WINS) {
        white_.addWin();
        black_.addLoss();
    } else if (r == GameResult::BLACK_WINS) {
        black_.addWin();
        white_.addLoss();
    } else if (r == GameResult::DRAW) {
        white_.addDraw();
        black_.addDraw();
    }
}

void Game::announceResult() const {
    board_.display(Color::WHITE); 
    cout << "\n============================================\n";
    cout << "                 GAME OVER                  \n";
    cout << "============================================\n";
    
    if (result_ == GameResult::WHITE_WINS) {
        cout << "White (" << white_.getName() << ") wins by Checkmate or Resignation!\n";
    } else if (result_ == GameResult::BLACK_WINS) {
        cout << "Black (" << black_.getName() << ") wins by Checkmate or Resignation!\n";
    } else if (result_ == GameResult::DRAW) {
        cout << "Game drawn by Stalemate or Agreement!\n";
    }
    
    cout << "============================================\n\n";
}

GameResult Game::start() {
    
    while (!processTurn()) {
        
    }
    
    announceResult();
    
    applyResult(result_);
    
    return result_;
}
