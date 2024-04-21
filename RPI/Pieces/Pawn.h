#include "../Piece.h"
#include <algorithm>

class Pawn : public Piece
{
public:
    Pawn(Color color, int pos);
    vector<int> calcLegalMoves();
    vector<int> getDiagonals() { return diagonals_; }
    vector<int> getEnPassant() { return enPassant_; }
    vector<int> getPawnLegalMoves() { return legalMoves_; }
private:
    vector<int> diagonals_;
    vector<int> enPassant_;
};