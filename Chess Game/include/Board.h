#pragma once
#include "Types.h"
#include "Piece.h"


class Board {
    private:
    Piece* grid_[8][8] = {nullptr};
    Square enPassantTarget_;

    void deepCopy(const Board& src);
    void clearBoard();
public:
    Board();
    Board(const Board& other); 
    Board& operator=(const Board& other);
    ~Board(); 

    void initialize();

    Piece* getPiece(Square sq) const;
    void setPiece(Square sq, Piece* piece);
    void removePiece(Square sq);

    void makeMove(const Move& move);

    Square getEnPassantTarget() const { 
        return enPassantTarget_; 
    }
    
   
    Square findKing(Color color) const;
    void display(Color pov) const;
    Board* clone() const; 


};
