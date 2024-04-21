#include "King.h"
#include "Rook.h"
#include "../Board.h"
#include <algorithm>

// King constructor
King::King(Color color, int pos) : Piece(color, pos, KING){
    legalMoves_ = {-9, -8, -7, -1, 1, 7, 8, 9};
}

// Calculate legal moves for the king
vector<int> King::calcLegalMoves()
{
    vector<int> moves; // vector of legal moves
    
    for (int move : legalMoves_) {
        int newPos = currentPos_ + move;
        if (newPos < 0 || newPos >= BOARD_SIZE) continue; //Go to next move if not within bounds

        int rowDiff = abs((newPos / ROW_LENGTH) - (currentPos_ / ROW_LENGTH));
        int colDiff = abs((newPos % ROW_LENGTH) - (currentPos_ % ROW_LENGTH));
        if ((rowDiff != 1 && colDiff != 1) || (rowDiff > 1 || colDiff > 1)) continue; //Must move 1 in either Col, Row or both

        Piece* p = board_->isSpotTaken(newPos);
        if (p != nullptr) { //Check if piece on spot
            if (p->getColor() == color_) {
                continue;
            }
        }
        if (!simulateMove(newPos)) continue; //Check if move puts king in check
        moves.emplace_back(newPos);      
    }

    //Check for castling
    if (!hasMoved()) {
        int castleMoves[2] = {-1, 1}; //Array for each direction
        for (int move : castleMoves) { // In each direction check if something is between rook and king
            for (int i = 1; i <= 4; i++) { //4 is since the farthest unmoved rook is 4 spaces away
                int newPos = currentPos_ + move * i;
                if (newPos < 0 || newPos >= BOARD_SIZE) break;
                Piece* p = board_->isSpotTaken(newPos);
                if (p != nullptr) {
                    if (p->getType() == ROOK && !(p->hasMoved())) {
                        moves.emplace_back(currentPos_ + move * 2); // Move 2 spaces towards the rook
                        break;
                    }
                    else 
                        break;
                }
            }
        }
    }    

    return moves;
}
