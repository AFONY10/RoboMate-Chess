#ifndef UART_H
#define UART_H

#include <QSerialPort>
#include <QObject>
#include <vector>
#include "uart.h"

class UART : public QObject
{
    Q_OBJECT
public:
    explicit UART(QObject *parent = nullptr);
    void dataHandler(QByteArray data);

private:
    QSerialPort* port_;
    UART* uart_;

public slots:
    void readData();
    void sendCapture(int);
    void sendLegalMoves(std::vector<int>);
    void sendMove(int, int);
signals:
    void pieceLifted(int);
    void piecePutDown(int);
    void pieceMoved();
    void illegalMove();
    // void setTurn();
};

#endif // UART_H
