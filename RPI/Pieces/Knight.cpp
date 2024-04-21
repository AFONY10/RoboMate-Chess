#include "Knight.h"
#include "../Board.h"
#include <algorithm>

// Knight constructor
Knight::Knight(Color color, int pos) : Piece(color, pos, KNIGHT){
    legalMoves_ = {-17, -15, -10, -6, 6, 10, 15, 17};
}

vector<int> Knight::calcLegalMoves()
{
    vector<int> moves; // vector of legal moves
    for (int move : legalMoves_) {
        int newPos = currentPos_ + move;
        if (newPos < 0 || newPos >= BOARD_SIZE) continue;

        int rowDiff = abs((newPos / 8) - (currentPos_ / 8));
        int colDiff = abs((newPos % 8) - (currentPos_ % 8));
            if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
                Piece* p = board_->isSpotTaken(newPos); // check if spot is taken
                if (p == nullptr) {
                    if (!simulateMove(newPos)) continue; //Check if move puts king in check
                    moves.emplace_back(newPos);
                }
                else if (p->getColor() != color_) {
                    if (!simulateMove(newPos)) continue; //Check if move puts king in check
                    moves.push_back(newPos);
                }
                else{
                    continue;
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
