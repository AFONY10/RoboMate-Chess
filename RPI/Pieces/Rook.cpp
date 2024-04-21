#include "Rook.h"
#include "../Board.h"
#include <algorithm>

// Rook constructor
Rook::Rook(Color color, int pos) : Piece(color, pos, ROOK) {
    legalMoves_ = {-8, -1, 1, 8};
}

// Calculate legal moves for the rook
vector<int> Rook::calcLegalMoves() {
    vector<int> moves;

    for (int move : legalMoves_) {
        for (int i = 1; i < ROW_LENGTH; i++) {
            int newPos = currentPos_ + move * i;
            if (newPos < 0 || newPos >= BOARD_SIZE) break; //Break if out of bounds

            int rowDiff = abs((newPos / ROW_LENGTH) - (currentPos_ / ROW_LENGTH));
            int colDiff = abs((newPos % ROW_LENGTH) - (currentPos_ % ROW_LENGTH));
            if (rowDiff > 0 && colDiff > 0) break; //Break if rook moves both col and row

            Piece* p = board_->isSpotTaken(newPos);
            if (p != nullptr) { //Check if piece on spot
                if (p->getColor() != color_) {
                    if (!simulateMove(newPos)) break; //Check if move puts king in check
                    moves.emplace_back(newPos);
                    break; //Break and add position if piece has opposite color
                }
                else {
                    break; //Break if piece has same color
                }
            }
            else {
                if (!simulateMove(newPos)) break; //Check if move puts king in check
                moves.emplace_back(newPos); //Add position if no piece on spot
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
