#include "../../include/pieces/King.h"
#include "../../include/Board.h"

wstring King::getSymbol() const {
    if (color_ == Color::WHITE) {
        return L"K";
    } else {
        return L"k";
    }
}

vector<Move> King::getPseudoMoves(const Board& board, Square from) const {
    vector<Move> moves;

    
    int rowDirs[8] = { 1, -1,  0,  0,  1,  1, -1, -1 };
    int colDirs[8] = { 0,  0,  1, -1,  1, -1,  1, -1 };

    for (int i = 0; i < 8; i++) {
        Square sq;
        sq.row = from.row + rowDirs[i];
        sq.col = from.col + colDirs[i];

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
