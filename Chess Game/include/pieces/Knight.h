#pragma once
#include "../Piece.h"


class Knight : public Piece {
public:
    Knight(Color color) : Piece(color) {}

    PieceType getType() const override { 
        return PieceType::KNIGHT; 
    }
    
    wstring getSymbol() const override;
    vector<Move> getPseudoMoves(const Board& board, Square from) const override;
    
    Piece* clone() const override {
        Knight* p = new Knight(color_);
        if (hasMoved_) {
            p->setMoved();
        }
        return p;
    }
};
