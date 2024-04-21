#include "resetwindow.h"
#include "ui_resetwindow.h"
#include "mainwindow.h"
//#include <QPixmap> // To insert pictures

// Constructor for the Reset window
ResetWindow::ResetWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetWindow)
{
    ui->setupUi(this);
        int screenWidth = 650;
        int screenHeight = 400;
        this->setFixedSize(screenWidth, screenHeight);

}

// Destructor for the Reset window
ResetWindow::~ResetWindow()
{
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

// Show the Reset window
void ResetWindow::showResetWindow() {
    show();
}

// Close the Reset window when the "Go back" button is clicked
void ResetWindow::on_pushButton_goBack_clicked()
{
    hide();
       if (auto mw = mainWindow.lock()) {
           mw->show();
       }
    emit closed();
}

