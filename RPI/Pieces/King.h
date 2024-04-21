#include "../Piece.h"

class King : public Piece
{
public:
    King(Color color, int pos);
    vector<int> calcLegalMoves();
};