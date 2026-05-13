#pragma once
#include "../Piece.h"


class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color) {}

    PieceType getType() const override { 
        return PieceType::BISHOP; 
    }
    
    wstring getSymbol() const override;
    vector<Move> getPseudoMoves(const Board& board, Square from) const override;
    
    Piece* clone() const override {
        Bishop* p = new Bishop(color_);
        if (hasMoved_) {
            p->setMoved();
        }
        return p;
    }
};
