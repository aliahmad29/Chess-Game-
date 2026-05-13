#include "../include/MoveValidator.h"


bool MoveValidator::isSquareAttacked(Square sq, Color byColor, const Board& board) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board.getPiece({r, c});
            if (p != nullptr && p->getColor() == byColor) {
                
                vector<Move> enemyMoves = p->getPseudoMoves(board, {r, c});
                
                for (int i = 0; i < enemyMoves.size(); i++) {
                    if (enemyMoves[i].to == sq) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool MoveValidator::leavesKingInCheck(const Move& move, Color color, const Board& board) {
    Board* testBoard = board.clone(); 
    
    testBoard->makeMove(move); 
    
    bool result = isInCheck(color, *testBoard);
    
    delete testBoard; 
    
    return result;
}

vector<Move> MoveValidator::getCastlingMoves(Color color, const Board& board) {
    vector<Move> castlingMoves;
    Square kingSq = board.findKing(color);
    if (!kingSq.isValid()) return castlingMoves;

    Piece* king = board.getPiece(kingSq);
    
    
    if (king == nullptr || king->hasMoved() || isInCheck(color, board)) {
        return castlingMoves;
    }

    int row = kingSq.row;
    Color opponent = opposite(color);

    
    Piece* rightRook = board.getPiece({row, 7});
    if (rightRook != nullptr && rightRook->getType() == PieceType::ROOK && rightRook->getColor() == color && !rightRook->hasMoved()) {
        if (board.getPiece({row, 5}) == nullptr && board.getPiece({row, 6}) == nullptr) {
            
            if (!isSquareAttacked({row, 5}, opponent, board) && !isSquareAttacked({row, 6}, opponent, board)) {
                Move m = {kingSq, {row, 6}, PieceType::NONE, true, false, false}; 
                castlingMoves.push_back(m);
            }
        }
    }

    
    Piece* leftRook = board.getPiece({row, 0});
    if (leftRook != nullptr && leftRook->getType() == PieceType::ROOK && leftRook->getColor() == color && !leftRook->hasMoved()) {
        if (board.getPiece({row, 1}) == nullptr && board.getPiece({row, 2}) == nullptr && board.getPiece({row, 3}) == nullptr) {
            if (!isSquareAttacked({row, 3}, opponent, board) && !isSquareAttacked({row, 2}, opponent, board)) {
                Move m = {kingSq, {row, 2}, PieceType::NONE, true, false, false};
                castlingMoves.push_back(m);
            }
        }
    }

    return castlingMoves;
}

vector<Move> MoveValidator::getLegalMovesFrom(Square from, const Board& board) {
    vector<Move> legalMoves;
    Piece* p = board.getPiece(from);
    if (p == nullptr) {
        return legalMoves;
    }

    Color c = p->getColor();
    vector<Move> pseudo = p->getPseudoMoves(board, from);

    
    for (int i = 0; i < pseudo.size(); i++) {
        if (!leavesKingInCheck(pseudo[i], c, board)) {
            legalMoves.push_back(pseudo[i]);
        }
    }

    
    if (p->getType() == PieceType::KING) {
        vector<Move> castling = getCastlingMoves(c, board);
        for(int i = 0; i < castling.size(); i++) {
            legalMoves.push_back(castling[i]);
        }
    }

    return legalMoves;
}


vector<Move> MoveValidator::getLegalMoves(Color color, const Board& board) {
    vector<Move> allLegal;
    
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board.getPiece({r, c});
            if (p != nullptr && p->getColor() == color) {
                vector<Move> pieceMoves = getLegalMovesFrom({r, c}, board);
                for(int i = 0; i < pieceMoves.size(); i++) {
                    allLegal.push_back(pieceMoves[i]);
                }
            }
        }
    }
    return allLegal;
}

bool MoveValidator::isLegalMove(const Move& move, Color color, const Board& board) {
    vector<Move> legalMoves = getLegalMovesFrom(move.from, board);
    for (int i = 0; i < legalMoves.size(); i++) {
        if (legalMoves[i].to == move.to && legalMoves[i].promotionPiece == move.promotionPiece) {
            return true;
        }
    }
    return false;
}

bool MoveValidator::isInCheck(Color color, const Board& board) {
    Square kingSq = board.findKing(color);
    if (!kingSq.isValid()) {
        return false;
    }
    return isSquareAttacked(kingSq, opposite(color), board);
}


bool MoveValidator::isCheckmate(Color color, const Board& board) {
    return isInCheck(color, board) && getLegalMoves(color, board).empty();
}


bool MoveValidator::isStalemate(Color color, const Board& board) {
    return !isInCheck(color, board) && getLegalMoves(color, board).empty();
}

Move MoveValidator::parseInput(string input, Color currentColor, const Board& board, bool& isValid) {
    Move badMove = {{-1, -1}, {-1, -1}, PieceType::NONE, false, false, false};
    isValid = false;

    
    if (input.length() != 5 && input.length() != 7) {
        return badMove;
    }

    if (input[2] != '-') {
        return badMove;
    }

    
    string fromStr = input.substr(0, 2);
    string toStr = input.substr(3, 2);
    
    Square from;
    from.row = fromStr[1] - '1';
    from.col = fromStr[0] - 'a';
    
    Square to;
    to.row = toStr[1] - '1';
    to.col = toStr[0] - 'a';

    PieceType promo = PieceType::NONE;
    if (input.length() == 7 && input[5] == '=') {
        char p = input[6];
        if (p == 'Q') promo = PieceType::QUEEN;
        else if (p == 'R') promo = PieceType::ROOK;
        else if (p == 'B') promo = PieceType::BISHOP;
        else if (p == 'N') promo = PieceType::KNIGHT;
    }

    
    vector<Move> legalMoves = getLegalMovesFrom(from, board);
    for (int i = 0; i < legalMoves.size(); i++) {
        if (legalMoves[i].to == to && legalMoves[i].promotionPiece == promo) {
            isValid = true;
            return legalMoves[i];
        }
    }
    
    Move basicMove = {from, to, promo, false, false, promo != PieceType::NONE};
    isValid = false; 
    return basicMove;
}
