#pragma once
#include "../Piece.h"


class Rook : public Piece {
public:
    Rook(Color color) : Piece(color) {}

    PieceType getType() const override { 
        return PieceType::ROOK; 
    }
    
    wstring getSymbol() const override;
    vector<Move> getPseudoMoves(const Board& board, Square from) const override;
    
    Piece* clone() const override {
        Rook* p = new Rook(color_);
        if (hasMoved_) {
            p->setMoved();
        }
        return p;
    }
};
