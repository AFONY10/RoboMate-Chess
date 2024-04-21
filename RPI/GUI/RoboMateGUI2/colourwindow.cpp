#include "colourwindow.h"
#include "ui_colourwindow.h"
#include "settingwindow.h"
#include <QLabel>

// Constructor for the colour window
ColourWindow::ColourWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColourWindow)

{
    ui->setupUi(this);
        int screenWidth = 650; 
        int screenHeight = 400; 
        this->setFixedSize(screenWidth, screenHeight);

}

// Destructor for the colour window
ColourWindow::~ColourWindow()
{
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

// Show the colour window
void ColourWindow::showColourWindow(){
    show();
}

// Close the colour window
void ColourWindow::on_pushButton_goBack_clicked()
{
    hide();
   if (auto sw = settingWindow.lock()) {
        sw->show();
    }
   emit closed();
}

// Set the colour of the pieces to white
void ColourWindow::on_pushButton_white_clicked()
{
    emit setColor(WHITE);
    std::cout<<"White is chosen"<<std::endl;
}

// Set the colour of the pieces to black
void ColourWindow::on_pushButton_black_clicked()
{
    emit setColor(BLACK);
    std::cout<<"Black is chosen"<<std::endl;
}

