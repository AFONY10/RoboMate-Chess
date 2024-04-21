#include "pvrmwindow.h"
#include "ui_pvrmwindow.h"
#include "mainwindow.h"
#include "../../Board.h"
#include "gameloopthread.h"
#include <QDebug>

// Constructor for the PvRM window
PvRMWindow::PvRMWindow(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::PvRMWindow)
{
    ui->setupUi(this);
        int screenWidth = 650; 
        int screenHeight = 400; 
        this->setFixedSize(screenWidth, screenHeight);

}

// Destructor for the PvRM window
PvRMWindow::~PvRMWindow()
{
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

// Show the PvRM window
void PvRMWindow::showPvRMWindow(){
    show();
}

// Shows the current players turn as text based on the colour
void PvRMWindow::setTurn(Color color) {
    if (color == WHITE)
        ui->label_turn->setText("White's turn");
    else
        ui->label_turn->setText("Black's turn");

}

// Close the PvRM window when the "Give up" button is clicked
void PvRMWindow::on_pushButton__giveUp_clicked()
{
    emit giveUp();
    hide();
    emit closed();
}

// Close the PvRM window when the "Go back" button is clicked
void PvRMWindow::on_pushButton_goBack_clicked()
{
    hide();
    emit closed();
}

// When "done" button is clicked, hide the label and button
void PvRMWindow::on_pushButton_actionCompleted_clicked()
{
    ui->hidden_Label->setVisible(false);
    ui->pushButton_actionCompleted->setVisible(false);
}

// Show that there is a queen promotion available
void PvRMWindow::showQueenPromotion(Color color ) {
    if (color == WHITE) {
        ui->hidden_Label->setText("Replace white's pawn with a white queen");
    }
    else {
        ui->hidden_Label->setText("Replace black's pawn with a black queen");
    }
    ui->pushButton_actionCompleted->setVisible(true);
    ui->hidden_Label->setVisible(true);
}

// Show that there is checkmate
void PvRMWindow::showCheckmate(Color color) {
    if (color == WHITE) {
        ui->hidden_Label->setText("White has been checkmated");
    }
    else {
        ui->hidden_Label->setText("Black has been checkmated");
    }
    ui->hidden_Label->setVisible(true);
    ui->pushButton_goBack->setVisible(true);
}

// Show that there is stalemate
void PvRMWindow::showStalemate() {
    ui->hidden_Label->setText("Stalemate");
    ui->hidden_Label->setVisible(true);
    ui->pushButton_goBack->setVisible(true);
}

// Show that there has been an illegal move
void PvRMWindow::showIllegalMove() {
    std::cout << "Showing Illegal moves" << std::endl;

    ui->hidden_Label->setText("Move is illegal, try again");

    ui->pushButton_actionCompleted->setVisible(true);
    ui->hidden_Label->setVisible(true);
}

// Debugging purposes
void PvRMWindow::on_pushButton_sendUart_clicked()
{
    std::cout << "UART sent" << std::endl;
    emit movePiece(1,18);
}

// Debugging purposes
void PvRMWindow::on_pushButton_e5_clicked()
{
    emit movePiece(12,28);
}

