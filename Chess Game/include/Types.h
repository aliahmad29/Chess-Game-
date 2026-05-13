#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;


enum class Color     { WHITE, BLACK, NONE };
enum class PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE };
enum class GameResult{ WHITE_WINS, BLACK_WINS, DRAW, ONGOING };


struct Square 
{
    int row ;
    int col ;

    
    bool isValid() const
    {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    
    bool operator==(const Square& o) const 
    {
        return row == o.row && col == o.col;
    }
    bool operator!=(const Square& o) const { 
        return !(*this == o); 
    }

    
    string toNotation() const {
        if (!isValid()) return "??";
        string s = "";
        s += static_cast<char>('a' + col);
        s += static_cast<char>('1' + row);
        return s;
    }
};

struct Move {
    Square from;
    Square to;
    PieceType promotionPiece = PieceType::NONE;
    bool isCastling = false;
    bool isEnPassant = false;
    bool isPromotion = false;
};


inline Color opposite(Color c) {
    if (c == Color::WHITE) {
        return Color::BLACK;
    } else {
        return Color::WHITE;
    }
}

inline string colorName(Color c) {
    if (c == Color::WHITE) {
        return "White";
    } else {
        return "Black";
    }
}
