#pragma once
#include "../Piece.h"


class Queen : public Piece {
public:
    Queen(Color color) : Piece(color) {}

    PieceType getType() const override { 
        return PieceType::QUEEN; 
    }
    
    wstring getSymbol() const override;
    vector<Move> getPseudoMoves(const Board& board, Square from) const override;
    
    Piece* clone() const override {
        Queen* p = new Queen(color_);
        if (hasMoved_) {
            p->setMoved();
        }
        return p;
    }
};
