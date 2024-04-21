#include "uart.h"
#include <QDebug>
#include <QString>
#include <bitset>

using namespace std;

// Constructor for the UART class
UART::UART(QObject *parent)
    : QObject{parent},
      port_(new QSerialPort)
{
    // Set up the UART port
    port_->setPortName("/dev/ttyAMA0");
    port_->setBaudRate(QSerialPort::Baud9600);
    port_->setDataBits(QSerialPort::Data8);
    port_->setParity(QSerialPort::NoParity);
    port_->setStopBits(QSerialPort::OneStop);
    port_->setFlowControl(QSerialPort::NoFlowControl);

    if (!port_->open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open port";
    }

    connect(port_, &QSerialPort::readyRead, this, &UART::readData);

    /*if (port_->isOpen()) {
        QString s = "Hej fra UART";
        QString d = "Sender besked med UART: " + s;
        qDebug() << d;
        QByteArray data = s.toUtf8();
        port_->write(data);
    }*/
}

// Read data from the UART port
void UART::readData() {
    QByteArray data = port_->readAll();
    dataHandler(data);
}

// Handle the data received from the UART port
void UART::dataHandler(QByteArray data) {
    qDebug() << "Recieved: " + data;
    // qDebug() << "Recieved: " + static_cast<int>(data[1]);
    switch(data[0]) {
    case 'o': // o = piece lifted
        emit pieceLifted(static_cast<int>(data[1]));
        break;
    case 'n': // n = piece put down
        emit piecePutDown(static_cast<int>(data[1]));
        // emit setTurn();
        break;
    case 's': // s = successful move
        emit pieceMoved();
        break;
    case 'e': // e = same position
        qDebug() << "Same position, go back to previous state";
        break;
    case 'i': // i = illegal move
        emit illegalMove();
        break;
    default: // Unknown data
        qDebug() << "Unknown Data Received";
        break;
    }

}

// Send the capture position to the PSoC
void UART::sendCapture(int capture)
{
    QByteArray data;
    data.append('d');
    data.append(capture);

    for (int i = 1; i < 8; i++) {
        char c = 0;
        data.append(c);
    }

    qDebug() << "Sending: " + data + " " + capture;
    port_->write(data);
}

// Send the legal moves to the PSoC
void UART::sendLegalMoves(vector<int> moves) {
    uint64_t legalBits = 0;

    for (int move : moves) {
        if (move >= 0 && move < 64) {
            legalBits |= (1ULL << move);
        }
    }

    QString dataString = "l";
    for (int i = 0; i < 64; i += 8) {
            unsigned long byte = (legalBits >> (56 - i)) & 0xFF;
            dataString += static_cast<char>(byte);
    }

    qDebug() << "Sending: " + dataString;
    port_->write(dataString.toUtf8());
}

// Send the move that RoboMate has chosen to the PSoC
void UART::sendMove(int from, int to)
{
    QByteArray data;
    data.append('m');
    data.append(from);
    data.append(to);

    for (int i = 2; i < 8; i++) {
        char c = 0;
        data.append(c);
    }

    qDebug() << "Sending: " + data + " " + from + " " + to;
    port_->write(data);
}

