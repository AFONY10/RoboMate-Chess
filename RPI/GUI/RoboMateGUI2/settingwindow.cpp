#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "mainwindow.h"
#include "difficultywindow.h"
#include "colourwindow.h"

// Constructor for the Setting window
SettingWindow::SettingWindow(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SettingWindow),
      difficultyWindow(std::make_unique<DifficultyWindow>(this)),
      colourWindow(std::make_unique<ColourWindow>(this))
{
    ui->setupUi(this);
        int screenWidth = 650;
        int screenHeight = 400;
        this->setFixedSize(screenWidth, screenHeight);

    connect(difficultyWindow.get(), &DifficultyWindow::closed, this, &SettingWindow::showSettingWindow);
    connect(colourWindow.get(), &ColourWindow::closed, this, &SettingWindow::showSettingWindow);

    connect(colourWindow.get(), &ColourWindow::setColor, this, &SettingWindow::setColor);
    connect(difficultyWindow.get(), &DifficultyWindow::setDifficulty, this, &SettingWindow::putDifficulty);
}

// Destructor for the Setting window
SettingWindow::~SettingWindow()
{
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

// Show the Setting window
void SettingWindow::showSettingWindow() {
    show();
}

// When the "Difficulty" button is clicked, hide the Setting window and show the Difficulty window
void SettingWindow::on_pushButton_difficulty_clicked()
{
    hide();
    difficultyWindow ->show();

}

// When the "Colour" button is clicked, hide the Setting window and show the Colour window
void SettingWindow::on_pushButton_colour_clicked()
{
    hide();
    colourWindow->show();  // Show the existing ColourWindow instance

}

// Close the Setting window when the "Go back" button is clicked
void SettingWindow::on_pushButton_goBack_clicked()
{
    hide();
       if (auto mw = mainWindow.lock()) {
           mw->show();
       }
    emit closed();
}

// Set the colour of the pieces to the chosen colour
void SettingWindow::setColor(Color color) {
    emit setPlayerColor(color);
}

// Set the difficulty of the game to the chosen difficulty
void SettingWindow::putDifficulty(int dif) {
    emit setDifficulty(dif);
}
