#include "../Piece.h"

class Rook : public Piece
{
public:
    Rook(Color color, int pos);
    vector<int> calcLegalMoves();
};