#include "pvpwindow.h"
#include "ui_pvpwindow.h"
#include "mainwindow.h"
#include "../../Board.h"
#include "gameloopthread.h"

// Constructor for the PvP window
PvPWindow::PvPWindow(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::PvPWindow)
{
    ui->setupUi(this);
        int screenWidth = 650;
        int screenHeight = 400;
        this->setFixedSize(screenWidth, screenHeight);

    ui->pushButton_goBack->setVisible(false);
    ui->hidden_Label->setVisible(false);
    ui->pushButton_actionCompleted->setVisible(false);

}

// Destructor for the PvP window
PvPWindow::~PvPWindow()
{
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

// Show the PvP window
void PvPWindow::showPvPWindow(){
    show();
}

// Shows the current players turn based on the colour
void PvPWindow::setTurn(Color color) {
    if (color == WHITE)
        ui->label->setText("White's turn");
    else
        ui->label->setText("Black's turn");
}

// Close the PvP window when the "Give up" button is clicked
void PvPWindow::on_pushButton__giveUp_clicked()
{
    emit giveUp();
    hide();
    emit closed();
}

// Close the PvP window when the "Go back" button is clicked
void PvPWindow::on_pushButton_goBack_clicked()
{
    ui->hidden_Label->setVisible(false);
    ui->pushButton_goBack->setVisible(false);
    ui->pushButton_actionCompleted->setVisible(false);
    hide();
    emit closed();
}

// When "done" button is clicked, hide the label and button
void PvPWindow::on_pushButton_actionCompleted_clicked()
{
    ui->hidden_Label->setVisible(false);
    ui->pushButton_actionCompleted->setVisible(false);
}

// Show that a pawn promotion is possible
void PvPWindow::showQueenPromotion(Color color ) {
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
void PvPWindow::showCheckmate(Color color) {
    if (color == WHITE) {
        ui->hidden_Label->setText("White has been checkmated");
    }
    else {
        ui->hidden_Label->setText("Black has been checkmated");
    }
    ui->hidden_Label->setVisible(true);
    ui->pushButton_goBack->setVisible(true);
}

// Show that there is a stalemate
void PvPWindow::showStalemate() {
    ui->hidden_Label->setText("Stalemate");
    ui->hidden_Label->setVisible(true);
    ui->pushButton_goBack->setVisible(true);
}

// Show that there is an illegal move
void PvPWindow::showIllegalMove() {
    std::cout << "Showing Illegal Moves" << std::endl;

    ui->hidden_Label->setText("Move is illegal, try again");

    ui->pushButton_actionCompleted->setVisible(true);
    ui->hidden_Label->setVisible(true);
}
