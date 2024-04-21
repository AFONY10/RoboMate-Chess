#include "../Piece.h"

class Knight : public Piece
{
public:
    Knight(Color color, int pos);
    vector<int> calcLegalMoves();

};