#include "Bishop.h"
#include "../Board.h"
#include <algorithm>

// Bishop constructor
Bishop::Bishop(Color color, int pos) : Piece(color, pos, BISHOP) {
    legalMoves_ = {9, 7, -7, -9};
}

// Get the row and column of the piece
void Bishop::getRowCol(int currentPos_, int &row, int &col)
{
    row = currentPos_ / ROW_LENGTH;
    col = currentPos_ % ROW_LENGTH;
}

// Calculate legal moves for the bishop
vector<int> Bishop::calcLegalMoves()
{
    vector<int> moves; // vector of legal moves
    int row, col;
    getRowCol(currentPos_, row, col);

    for (int move : legalMoves_){
        for (int i = 1; i < ROW_LENGTH; i++){
            int newPos = currentPos_ + move * i;
            if (newPos < 0 || newPos >= BOARD_SIZE) break; //Break if out of bounds

            int rowDiff = abs((newPos / ROW_LENGTH) - (currentPos_ / ROW_LENGTH));
            int colDiff = abs((newPos % ROW_LENGTH) - (currentPos_ % ROW_LENGTH));
            if (rowDiff != i || colDiff != i) break; //Break if bishop moves both col and row

            Piece* p = board_->isSpotTaken(newPos);
            if (p != nullptr) { //Check if piece on spot
                if (p->getColor() != getColor()) {
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
