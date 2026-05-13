#pragma once
#include "../Piece.h"


class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color) {}

    PieceType getType() const override { 
        return PieceType::PAWN; 
    }
    
    wstring getSymbol() const override;
    vector<Move> getPseudoMoves(const Board& board, Square from) const override;
    
    Piece* clone() const override {
        Pawn* p = new Pawn(color_);
        if (hasMoved_) {
            p->setMoved();
        }
        return p;
    }
};
