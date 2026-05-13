#pragma once
#include "Board.h"


class MoveValidator {
private:
    static vector<Move> getCastlingMoves(Color color, const Board& board);

   
    static bool leavesKingInCheck(const Move& move, Color color, const Board& board);
public:
    static vector<Move> getLegalMoves(Color color, const Board& board);
    static vector<Move> getLegalMovesFrom(Square from, const Board& board);
    static bool isLegalMove(const Move& move, Color color, const Board& board);

    static bool isInCheck(Color color, const Board& board);
    static bool isCheckmate(Color color, const Board& board);
    static bool isStalemate(Color color, const Board& board);

    static bool isSquareAttacked(Square sq, Color byColor, const Board& board);
    
   
    static Move parseInput(string input, Color currentColor, const Board& board, bool& isValid);

};
