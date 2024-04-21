#include "../Piece.h"

class Queen : public Piece
{
public:
    Queen(Color color, int pos);
    vector<int> calcLegalMoves();

};