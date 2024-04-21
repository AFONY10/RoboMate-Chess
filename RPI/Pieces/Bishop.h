#include "../Piece.h"

class Bishop : public Piece
{
public:
    Bishop(Color color, int pos);
    vector<int> calcLegalMoves();
    void getRowCol(int currentPos_, int& row, int& col);

};