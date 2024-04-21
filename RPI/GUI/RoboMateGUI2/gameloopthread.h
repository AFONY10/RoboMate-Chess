/*#ifndef GAMELOOPTHREAD_H
#define GAMELOOPTHREAD_H

#include <QObject>
#include "../../Board.h"
#include <QThread>
#include <QMutex>

class GameLoopThread : public QThread {
    Q_OBJECT
public:
    GameLoopThread(Board* b)
        : QThread(),
          board(b)
    {
        turn = WHITE;
        connect(board, &Board::changeTurn, this, &GameLoopThread::changeTurn);
        connect(board, &Board::queenPromotion, this, &GameLoopThread::queenPromotion);
        connect(board, &Board::checkMate, this, &GameLoopThread::checkMate);
        connect(board, &Board::staleMate, this, &GameLoopThread::staleMate);
    }

public slots:
    void playerResign() {
        if (board) {
            board->playerResign();
        }
    }

    void setGameMode(GameMode gm) {
        currentGameMode = gm;
    }

    void changeTurn() {
        turn = turn == WHITE ? BLACK : WHITE;
        emit setTurn(turn);
    }

    void setPlayerColor(Color color) {
        board->setPlayerColor(color);
    }

    void queenPromotion (Color color) {
        emit promoteQueen(color);
    }

    void checkMate (Color color) {
        emit checkMated(color);
    }

    void staleMate(Color color) {
        emit staleMated(color);
    }

signals:
    void threadStarted();
    void threadFinished();
    void setTurn(Color color);
    void promoteQueen(Color color);
    void checkMated(Color color);
    void staleMated(Color color);

protected:
    void run() override {
        emit threadStarted();
        if (board) {
            if (currentGameMode == PVP) {
                turn = WHITE;
                //board->gameLoop1v1();
            }
            else {
                turn = board->getPlayerColor();
                //board->gameLoop1vBot();
            }
        }
        emit threadFinished();
    }

private:
    Board* board;
    GameMode currentGameMode;
    Color turn;
};


#endif //GAMELOOPTHREAD_H
*/
