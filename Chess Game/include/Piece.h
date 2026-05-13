#pragma once
#include "Types.h"

class Board; 


class Piece {


protected:
    Color color_;
    bool hasMoved_;
public:

    Piece(Color color) {
        color_ = color;
        hasMoved_ = false; 
    }
    
    virtual ~Piece() {}
    
    
    virtual PieceType getType() const = 0;
    virtual wstring getSymbol() const = 0;
    
    
    virtual vector<Move> getPseudoMoves(const Board& board, Square from) const = 0;
    
    
    virtual Piece* clone() const = 0;
    
    Color getColor() const { 
        return color_; 
    }
    
    bool hasMoved() const { 
        return hasMoved_; 
    }
    
    void setMoved() { 
        hasMoved_ = true; 
    }

};
