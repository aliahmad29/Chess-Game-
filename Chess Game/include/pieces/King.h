#pragma once
#include "../Piece.h"
class King : public Piece {
public:
    King(Color color) : Piece(color) {}

    PieceType getType() const override { 
        return PieceType::KING; 
    }
    
    wstring getSymbol() const override;
    vector<Move> getPseudoMoves(const Board& board, Square from) const override;
    
    Piece* clone() const override {
        King* p = new King(color_);
        if (hasMoved_) {
            p->setMoved();
        }
        return p;
    }
};
