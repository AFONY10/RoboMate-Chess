#include "Pawn.h"
#include "../Board.h"

// Pawn constructor
Pawn::Pawn(Color color, int pos) : Piece(color, pos, PAWN){
    if (color_ == WHITE) { //If white, move up
        legalMoves_ = { 8 };
        diagonals_ = { 7, 9 }; //Diagonal moves for pawn (for taking pieces)
    }
    else { //If black, move down
        legalMoves_ = { -8 };
        diagonals_ = { -7, -9 };
    }
    enPassant_ = { 1, -1 }; //En passant check for enemy pawns
}

// Calculate legal moves for the pawn
vector<int> Pawn::calcLegalMoves()
{
    vector<int> moves;
    vector<int> tempLegal = legalMoves_; //So we can manipulate legalMoves array temporarily
    
    if (!hasMoved_) { //If pawn hasn't moved, it can move 2 spaces
        tempLegal.push_back(tempLegal[0] * 2);
    }

    for (int move : tempLegal) {
        int newPos = currentPos_ + move;
        if (newPos < 0 || newPos >= BOARD_SIZE) continue; //Break if out of bounds

        Piece* p = board_->isSpotTaken(newPos);
        if (p != nullptr) { //Check if piece on spot
            continue; //Break if piece is on spot
        }
        else {
            if (!simulateMove(newPos)) continue; //Check if move puts king in check
            moves.emplace_back(newPos); //Add position if no piece on spot
        }
    }

    for (int move : diagonals_) { //Check for diagonal moves (taking pieces)
        int newPos = currentPos_ + move;
        if (newPos < 0 || newPos >= BOARD_SIZE) continue; //Break if out of bounds

        Piece* p = board_->isSpotTaken(newPos);
        if (p != nullptr) { //Check if piece on spot
            if (p->getColor() != color_) {
                if (!simulateMove(newPos)) continue; //Check if move puts king in check
                moves.emplace_back(newPos);
            }
        }
    }

    for (int move : enPassant_) { //Check for en passant
        int newPos = currentPos_ + move;
        if (newPos < 0 || newPos >= BOARD_SIZE) continue; //Break if out of bounds

        Piece* p = board_->isSpotTaken(newPos);
        if (p != nullptr && p->getType() == PAWN) { //If there is a pawn on the spot
            if (p->getColor() != color_) {  
                pair<int, int> lastMove = board_->getLastMove();
                if (lastMove.first == lastMove.second + legalMoves_[0] * 2 && lastMove.second == newPos) { //If pawn comes from 2 spaces away and lands next to pawn
                   if (!simulateMove(newPos)) continue; //Check if move puts king in check
                   moves.emplace_back(newPos + legalMoves_[0]); //Add postion that is 1 space fowards of the pawn next to it
                }
            }
        }
    }

    // Check if any of the moves are defending the king
    vector<int> defendingMoves = board_->getCheckDefendingMoves(getColor());
    if (!defendingMoves.empty()) {
        vector<int> newMoves;
        for (int move : moves) {
            if (find(defendingMoves.begin(), defendingMoves.end(), move) != defendingMoves.end()) {
                newMoves.push_back(move);
            }
        }
        moves = newMoves;
    }

    return moves;
}

