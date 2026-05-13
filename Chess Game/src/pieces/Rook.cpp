#include "../../include/pieces/Rook.h"
#include "../../include/Board.h"

wstring Rook::getSymbol() const {
    if (color_ == Color::WHITE) {
        return L"R";
    } else {
        return L"r";
    }
}

vector<Move> Rook::getPseudoMoves(const Board& board, Square from) const {
    vector<Move> moves;

    
    int rowDirs[4] = {1, -1, 0, 0};
    int colDirs[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        Square sq;
        sq.row = from.row + rowDirs[i];
        sq.col = from.col + colDirs[i];

        
        while (sq.isValid()) {
            Piece* p = board.getPiece(sq);
            
            if (p == nullptr) {
                moves.push_back({from, sq, PieceType::NONE, false, false, false});
            } else {
                
                if (p->getColor() != color_) {
                    moves.push_back({from, sq, PieceType::NONE, false, false, false});
                }
                break; 
            }
            
            sq.row += rowDirs[i];
            sq.col += colDirs[i];
        }
    }
    
    return moves;
}
