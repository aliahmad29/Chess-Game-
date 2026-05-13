#include "../../include/pieces/Knight.h"
#include "../../include/Board.h"

wstring Knight::getSymbol() const {
    if (color_ == Color::WHITE) {
        return L"N";
    } else {
        return L"n";
    }
}

vector<Move> Knight::getPseudoMoves(const Board& board, Square from) const {
    vector<Move> moves;

    
    int rowJumps[8] = { 2,  2, -2, -2,  1,  1, -1, -1 };
    int colJumps[8] = { 1, -1,  1, -1,  2, -2,  2, -2 };

    for (int i = 0; i < 8; i++) {
        Square sq;
        sq.row = from.row + rowJumps[i];
        sq.col = from.col + colJumps[i];

        if (!sq.isValid()) {
            continue;
        }

        Piece* p = board.getPiece(sq);
        
        
        if (p == nullptr || p->getColor() != color_) {
            moves.push_back({from, sq, PieceType::NONE, false, false, false});
        }
    }
    
    return moves;
}
