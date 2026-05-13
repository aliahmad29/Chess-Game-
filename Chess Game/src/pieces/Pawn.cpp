#include "../../include/pieces/Pawn.h"
#include "../../include/Board.h"

wstring Pawn::getSymbol() const {
    if (color_ == Color::WHITE) {
        return L"P";
    } else {
        return L"p";
    }
}

vector<Move> Pawn::getPseudoMoves(const Board& board, Square from) const {
    vector<Move> moves;

    int dir;
    int startRow;
    int promotionRow;

    
    if (color_ == Color::WHITE) {
        dir = 1;         
        startRow = 1;    
        promotionRow = 7;
    } else {
        dir = -1;        
        startRow = 6;    
        promotionRow = 0;
    }

   
    Square oneAhead;
    oneAhead.row = from.row + dir;
    oneAhead.col = from.col;

    if (oneAhead.isValid() && board.getPiece(oneAhead) == nullptr) {
       
        if (oneAhead.row == promotionRow) {
            moves.push_back({from, oneAhead, PieceType::QUEEN, false, false, true});
            moves.push_back({from, oneAhead, PieceType::ROOK, false, false, true});
            moves.push_back({from, oneAhead, PieceType::BISHOP, false, false, true});
            moves.push_back({from, oneAhead, PieceType::KNIGHT, false, false, true});
        } else {
            moves.push_back({from, oneAhead, PieceType::NONE, false, false, false});
        }

        
        if (from.row == startRow) {
            Square twoAhead;
            twoAhead.row = from.row + (2 * dir);
            twoAhead.col = from.col;

            if (board.getPiece(twoAhead) == nullptr) {
                moves.push_back({from, twoAhead, PieceType::NONE, false, false, false});
            }
        }
    }

    
    int attackCols[2] = { -1, 1 };
    
    for (int i = 0; i < 2; i++) {
        Square diag;
        diag.row = from.row + dir;
        diag.col = from.col + attackCols[i];

        if (diag.isValid()) {
            Piece* target = board.getPiece(diag);

            
            if (target != nullptr && target->getColor() != color_) {
                if (diag.row == promotionRow) {
                    moves.push_back({from, diag, PieceType::QUEEN, false, false, true});
                    moves.push_back({from, diag, PieceType::ROOK, false, false, true});
                    moves.push_back({from, diag, PieceType::BISHOP, false, false, true});
                    moves.push_back({from, diag, PieceType::KNIGHT, false, false, true});
                } else {
                    moves.push_back({from, diag, PieceType::NONE, false, false, false});
                }
            }

            
            Square ep = board.getEnPassantTarget();
            if (ep.isValid() && diag == ep && target == nullptr) {
                moves.push_back({from, diag, PieceType::NONE, false, true, false});
            }
        }
    }

    return moves;
}
