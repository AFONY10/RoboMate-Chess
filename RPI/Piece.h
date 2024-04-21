#pragma once
#include <vector>
#include <iostream>
#include <cmath>

enum Color {
    WHITE,  //=0
    BLACK   //=1
};

enum Type {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

using namespace std;

class Board;

class Piece {
public:
    Piece(Color color, int pos, Type type);
    virtual ~Piece() = default;
    vector<int> getLegalMoves();
    virtual vector<int> calcLegalMoves() = 0;
    Color getColor();
    Type getType();
    void setPos(int pos);
    int getPos() const { return currentPos_; }
    void updateBoard(Board* b);
    bool hasMoved() const { return hasMoved_; };
    bool updateLegalMoves();
protected:
    bool simulateMove(int to);
    Color color_;
    int currentPos_;
    bool hasMoved_;
    Type type_;
    vector<int> legalMoves_;
    Board* board_;
    vector<int> allLegalMoves_;
    static bool currentlySimulatingMove_;
};
