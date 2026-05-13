#include "../include/Board.h"
#include "../include/pieces/Pawn.h"
#include "../include/pieces/Rook.h"
#include "../include/pieces/Knight.h"
#include "../include/pieces/Bishop.h"
#include "../include/pieces/Queen.h"
#include "../include/pieces/King.h"
#include <iostream>
#include <cmath>

Board::Board() {
    
    for (int r = 0; r < 8; r++) 
    {
        for (int c = 0; c < 8; c++) 
        {
            grid_[r][c] = nullptr;
        }
    }
    initialize();
}

Board::Board(const Board& other)
{
    deepCopy(other);
}

Board& Board::operator=(const Board& other) 
{
    if (this != &other)
    {
        clearBoard();     
        deepCopy(other);  
    }
    return *this;
}

Board::~Board() {
    clearBoard();
}
void Board::clearBoard()
{
    for (int r = 0; r < 8; r++) 
    {
        for (int c = 0; c < 8; c++)
        {
            if (grid_[r][c] != nullptr) 
            {
                delete grid_[r][c]; 
                grid_[r][c] = nullptr;
            }
        }
    }
}

void Board::deepCopy(const Board& src)
{
    for (int r = 0; r < 8; r++) 
    {
        for (int c = 0; c < 8; c++)
        {
            if (src.grid_[r][c] != nullptr)
            {
                grid_[r][c] = src.grid_[r][c]->clone();
            } 
            else {
                grid_[r][c] = nullptr;
            }
        }
    }
    enPassantTarget_ = src.enPassantTarget_;
}

Board* Board::clone() const {
    return new Board(*this);
}

Piece* Board::getPiece(Square sq) const {
    if (!sq.isValid()) return nullptr;
    return grid_[sq.row][sq.col];
}

void Board::setPiece(Square sq, Piece* piece) {
    if (sq.isValid()) {
        if (grid_[sq.row][sq.col] != nullptr) {
            delete grid_[sq.row][sq.col];
        }
        grid_[sq.row][sq.col] = piece;
    }
}

void Board::removePiece(Square sq) {
    if (sq.isValid()) {
        if (grid_[sq.row][sq.col] != nullptr) {
            delete grid_[sq.row][sq.col]; 
        }
        grid_[sq.row][sq.col] = nullptr;
    }
}

// scan the board to find where the king is hiding
Square Board::findKing(Color color) const {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = getPiece({r, c});
            if (p != nullptr && p->getType() == PieceType::KING && p->getColor() == color) {
                return {r, c};
            }
        }
    }
    return {-1, -1}; 
}

// put all pieces in standard start positions
void Board::initialize() {
    clearBoard(); 

    enPassantTarget_ = {-1, -1}; 

    for (int c = 0; c < 8; c++) {
        grid_[1][c] = new Pawn(Color::WHITE);
        grid_[6][c] = new Pawn(Color::BLACK);
    }

    grid_[0][0] = new Rook(Color::WHITE);
    grid_[0][7] = new Rook(Color::WHITE);
    grid_[7][0] = new Rook(Color::BLACK);
    grid_[7][7] = new Rook(Color::BLACK);

    grid_[0][1] = new Knight(Color::WHITE);
    grid_[0][6] = new Knight(Color::WHITE);
    grid_[7][1] = new Knight(Color::BLACK);
    grid_[7][6] = new Knight(Color::BLACK);

    grid_[0][2] = new Bishop(Color::WHITE);
    grid_[0][5] = new Bishop(Color::WHITE);
    grid_[7][2] = new Bishop(Color::BLACK);
    grid_[7][5] = new Bishop(Color::BLACK);

    grid_[0][3] = new Queen(Color::WHITE);
    grid_[7][3] = new Queen(Color::BLACK);

    grid_[0][4] = new King(Color::WHITE);
    grid_[7][4] = new King(Color::BLACK);
}

void Board::makeMove(const Move& move)
{
    if (!move.from.isValid() || !move.to.isValid()) return;

    Piece* movingPiece = getPiece(move.from);
    if (movingPiece == nullptr) return;

    Square nextEnPassant = {-1, -1};

    // record en passant target if pawn double jumps
    if (movingPiece->getType() == PieceType::PAWN && abs(move.from.row - move.to.row) == 2) {
        int dir;
        if (movingPiece->getColor() == Color::WHITE)
        {
            dir = 1;
        } else {
            dir = -1;
        }
        nextEnPassant.row = move.from.row + dir;
        nextEnPassant.col = move.from.col;
    }

    // handle en passant capture (kill piece behind us)
    if (move.isEnPassant)
    {
        int captureRow = move.from.row; 
        int captureCol = move.to.col;
        removePiece({captureRow, captureCol});
    }

    // handle castling (move the rook )
    if (move.isCastling)
    {
        if (move.to.col == 6) 
        { 
            Piece* rook = grid_[move.to.row][7];
            grid_[move.to.row][7] = nullptr;
            grid_[move.to.row][5] = rook;
        }
        else if (move.to.col == 2) 
        { 
            Piece* rook = grid_[move.to.row][0];
            grid_[move.to.row][0] = nullptr;
            grid_[move.to.row][3] = rook;
        }
    }

    movingPiece->setMoved();

    // kill target square piece if any
    removePiece(move.to);

    // move pointer in array
    grid_[move.to.row][move.to.col] = movingPiece;
    grid_[move.from.row][move.from.col] = nullptr; 

    // handle promotion (swap piece)
    if (move.isPromotion && move.promotionPiece != PieceType::NONE)
    {
        Color c = movingPiece->getColor();
        
        removePiece(move.to);
        
        if (move.promotionPiece == PieceType::QUEEN)
        {
            grid_[move.to.row][move.to.col] = new Queen(c);
        }
        else if (move.promotionPiece == PieceType::ROOK)
        {
            grid_[move.to.row][move.to.col] = new Rook(c);
        } 
        else if (move.promotionPiece == PieceType::BISHOP)
        {
            grid_[move.to.row][move.to.col] = new Bishop(c);
        }
        else if (move.promotionPiece == PieceType::KNIGHT)
        {
            grid_[move.to.row][move.to.col] = new Knight(c);
        }
    }

    enPassantTarget_ = nextEnPassant;
}

// prints board in terminal
void Board::display(Color pov) const {
    wcout << L"\n";

    if (pov == Color::WHITE) {
        wcout << L"    a   b   c   d   e   f   g   h\n";
        wcout << L"  +---+---+---+---+---+---+---+---+\n";
        for (int r = 7; r >= 0; r--) {
            wcout << L"" << (r + 1) << L" |";
            for (int c = 0; c < 8; c++) {
                Piece* p = getPiece({r, c});
                if (p != nullptr) {
                    wcout << L" " << p->getSymbol() << L" |";
                } else {
                    wcout << L"   |";
                }
            }
            wcout << L" " << (r + 1) << L"\n";
            wcout << L"  +---+---+---+---+---+---+---+---+\n";
        }
        wcout << L"    A   B   C   D   E   F   G   H\n\n";
    } else 
    {
        wcout << L"    H   G   F   E   D   C   B   A\n";
        wcout << L"  +---+---+---+---+---+---+---+---+\n";
        for (int r = 0; r < 8; r++) {
            wcout << L"" << (r + 1) << L" |";
            for (int c = 7; c >= 0; c--) {
                Piece* p = getPiece({r, c});
                if (p != nullptr) {
                    wcout << L" " << p->getSymbol() << L" |";
                } else {
                    wcout << L"   |";
                }
            }
            wcout << L" " << (r + 1) << L"\n";
            wcout << L"  +---+---+---+---+---+---+---+---+\n";
        }
        wcout << L"    h   g   f   e   d   c   b   a\n\n";
    }
}
