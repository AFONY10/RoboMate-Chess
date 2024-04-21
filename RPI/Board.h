#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <vector>
#include <string>
#include "Piece.h"
#include "Chess_engine.h"

const int BOARD_SIZE = 64;
const int ROW_LENGTH = 8;

using namespace std;

class Pawn;

enum Gamemode {
    PVP,
    PVE
};

enum State {
    NOT_INGAME,
    WAITING_FOR_DEAD_PIECE,
    WAITING_FOR_MOVE_PIECE,
    WAITING_FOR_CASTLE_MOVE,
    WAITING_FOR_PLACE_PIECE,
    WAITING_FOR_LIFT_PIECE,
    WAITING_FOR_LIFT_PIECE_IL,
    WAITING_FOR_PLACE_PIECE_IL
};

class Board : public QObject {
    Q_OBJECT
public:
    Board();
    ~Board();
    bool setPos();
    Piece* isSpotTaken(int pos);
    vector<int> getLegalMoves(int pos);
    vector<Piece*> getOppositeColors(Color currentColor);
    Chess_engine& getBot();
    vector<Piece*> getPiecesCheckingKing(Color color);
    vector<int> getCheckDefendingMoves(Color color);
    bool checkForCheckmate(Color color);
    bool checkForStalemate(Color color);
    bool updateLegalMoves(Color color);
    bool simulateMove(int fromPos, int toPos);
    string getBoardString();
    bool hasBoardBeen3Times();
    bool deadPosition();
    void setLastMove(int from, int to);
    pair<int, int> getLastMove() { return lastMove_; }
    Color getPlayerColor() const { return playerColor_; }
    void printBoard() const;        //zTEST FUNKTION - TIL DEBUGGING - FJERNES VED ENDELIGT PRODUKT
    void printBoardWithLegalMoves(const vector<int>&) const;
    void gameLoop1v1();
    void gameLoop1vBot();
private:
    vector<Piece*> board_;
    vector<string> previousBoards_;
    Chess_engine bot_;
    int difficulty_ = 20;
    Color playerColor_ = WHITE;
    Piece* blackKing_ = nullptr;
    Piece* whiteKing_ = nullptr;
    bool whiteCanMove_ = true;
    bool blackCanMove_ = true;
    int movesSinceCapture_ = 0;
    pair<int, int> lastMove_ = { -1, -1 };
    bool playerResigned_ = false;

    void checkForEnpassantCapture(int, int, Pawn *);
    void didMovePiece();
    void didCapturePiece();
    void makeBotMove();
    void setState(State s);

    Gamemode gamemode_ = PVP;
    bool isGameRunning_ = false;
    int fromPos_ = -1;
    int toPos_ = -1;
    Color turn_ = WHITE;
    State state_ = NOT_INGAME;
public slots:
    void didLiftPiece(int);
    void didPlacePiece(int);
    void didStartGame(bool);
    void didPlayerResign();
    void didFinishMovePiece();
    void setPlayerColor(Color color);
    void setDifficulty(int difficulty);
    void resetBoard();
signals:
    void changeTurn(Color color);
    void queenPromotion(Color color);
    void checkMate(Color color);
    void staleMate();
    void legalmoves(vector<int> legalMoves);
    void capturePiece(int pos);
    void movePiece(int fromPos, int toPos);
    void illegalMove();
};

#endif // BOARD_H
