#include "Piece.h"
#include "Board.h"

// Piece constructor
Piece::Piece(Color color, int pos, Type type)
    : color_(color), currentPos_(pos), hasMoved_(false), type_(type), board_(nullptr), allLegalMoves_(0)
{
    
}

// Return alle legal moves for the piece
vector<int> Piece::getLegalMoves() {
    return allLegalMoves_;
}

// Return the color of the piece
Color Piece::getColor() {
    return color_;
}

// Return the type of the piece
Type Piece::getType() {
    return type_;
}

// Set the position of the piece
void Piece::setPos(int pos) {
    currentPos_ = pos;
    hasMoved_ = true; 
}

// Update the board pointer
void Piece::updateBoard(Board* b) {
    board_ = b;
}

// Return true if legal moves are possible, false if not
bool Piece::updateLegalMoves() {
    allLegalMoves_ = calcLegalMoves();
    if (allLegalMoves_.size() == 0) {
        return false;
    }
    else {
        return true;
    }
}

bool Piece::simulateMove(int to) {
    bool isLegal = true;
    if (!currentlySimulatingMove_) {
        currentlySimulatingMove_ = true;
        if (!board_->simulateMove(currentPos_, to)) {
            currentlySimulatingMove_ = false;
            isLegal = false;
        }
        currentlySimulatingMove_ = false;
    }
    return isLegal;
}

bool Piece::currentlySimulatingMove_ = false;
