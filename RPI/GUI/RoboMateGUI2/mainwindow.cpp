#include <memory> // Using smart pointers
#include "gameloopthread.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Include the other windows
#include "pvpwindow.h"
#include "settingwindow.h"
#include "pvrmwindow.h"
#include "resetwindow.h"
#include "difficultywindow.h"
#include <QSerialPort>
#include <QDebug>

// Constructor for the main window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      //thread_(new GameLoopThread(b)),
      board_(new Board),
      uart_(new UART),
      ui(new Ui::MainWindow),
      pvpWindow(std::make_unique<PvPWindow>(this)),
      settingWindow(std::make_unique<SettingWindow>(this)),
      pvrmWindow(std::make_unique<PvRMWindow>(this)),
      resetWindow(std::make_unique<ResetWindow>(this)),
      difficultyWindow(std::make_unique<DifficultyWindow>(this))
{
    ui->setupUi(this);

    // Connect syntax for Window navigation, go back to mainWindow
    connect(pvpWindow.get(), &PvPWindow::closed, this, &MainWindow::showMainWindow);
    connect(settingWindow.get(), &SettingWindow::closed, this, &MainWindow::showMainWindow);
    connect(pvrmWindow.get(), &PvRMWindow::closed, this, &MainWindow::showMainWindow);
    connect(resetWindow.get(), &ResetWindow::closed, this, &MainWindow::showMainWindow);

    // Emit and connect signals for when giveUp is pressed in gamemenu windows

    connect(pvpWindow.get(), &PvPWindow::giveUp, board_, &Board::didPlayerResign);
    connect(pvrmWindow.get(), &PvRMWindow::giveUp, board_, &Board::didPlayerResign);

    // Change and setTurn from Board in Gameplay windows
    connect(board_, &Board::changeTurn, pvpWindow.get(), &PvPWindow::setTurn);
    connect(board_, &Board::changeTurn, pvrmWindow.get(), &PvRMWindow::setTurn);

    // Emit and connect signals for color- and difficultychange from settingswindow to Board
    connect(settingWindow.get(), &SettingWindow::setPlayerColor, board_, &Board::setPlayerColor);
    connect(settingWindow.get(), &SettingWindow::setDifficulty, board_, &Board::setDifficulty);

    // Show queen promotion signal from Board to gameplay windows
    connect(board_, &Board::queenPromotion, pvrmWindow.get(), &PvRMWindow::showQueenPromotion);
    connect(board_, &Board::queenPromotion, pvpWindow.get(), &PvPWindow::showQueenPromotion);

    // Show check mate messag, signal from Board to gameplay windows
    connect(board_, &Board::checkMate, pvrmWindow.get(), &PvRMWindow::showCheckmate);
    connect(board_, &Board::checkMate, pvpWindow.get(), &PvPWindow::showCheckmate);

    // Show stale mate message, signal from Board to gameplay windows
    connect(board_, &Board::staleMate, pvrmWindow.get(), &PvRMWindow::showStalemate);
    connect(board_, &Board::staleMate, pvpWindow.get(), &PvPWindow::showStalemate);

    // Signals from UART to Board and gameplay windows, to communicate with PSoC
    connect(uart_, &UART::pieceLifted, board_, &Board::didLiftPiece);
    connect(uart_, &UART::piecePutDown, board_, &Board::didPlacePiece);
    connect(uart_, &UART::pieceMoved, board_, &Board::didFinishMovePiece);
    connect(uart_, &UART::illegalMove, pvpWindow.get(), &PvPWindow::showIllegalMove);
    connect(uart_, &UART::illegalMove, pvrmWindow.get(), &PvRMWindow::showIllegalMove);

    // Signals from Board to UART, to send chess logic to PSoC
    connect(board_, &Board::legalmoves, uart_, &UART::sendLegalMoves);
    connect(board_, &Board::capturePiece, uart_, &UART::sendCapture);
    connect(board_, &Board::movePiece, uart_, &UART::sendMove);

    // Display illegal move messages in gameplaywindows
    connect(board_, &Board::illegalMove, pvrmWindow.get(), &PvRMWindow::showIllegalMove);
    connect(board_, &Board::illegalMove, pvpWindow.get(), &PvPWindow::showIllegalMove);

    // Signal to start and reset game from MainWindow buttons to Board class
    connect(this, &MainWindow::startGame, board_, &Board::didStartGame);
    connect(this, &MainWindow::reset, board_, &Board::resetBoard);

    // Signal to test UART communcation, send UART through button in game play window
    connect(pvrmWindow.get(), &PvRMWindow::movePiece, uart_, &UART::sendMove);

    // Emit/connects difficulty setting to Board
    connect(difficultyWindow.get(), &DifficultyWindow::setDifficulty, board_, &Board::setDifficulty);
}

// Destructor for the main window
MainWindow::~MainWindow()
{

    if (board_) {
        std::cout << "Board destrcutor called, MW" << std::endl;
        delete board_;
        board_ = nullptr;
        std::cout << "Board destrcutor called finished, MW" << std::endl;
    }
    if (uart_) {
        std::cout << "UART destrcutor called, MW" << std::endl;
        delete uart_;
        uart_ = nullptr;
        std::cout << "UART destrcutor success, MW" << std::endl;
    }
    if (ui) {
        std::cout << "UI destrcutor called, MW" << std::endl;
        delete ui;
        ui = nullptr;
        std::cout << "UI destrcutor finished, MW" << std::endl;
    }

}

// Show the main window
void MainWindow::showMainWindow() {
    show();
}

// Close the main window and show the setting window
void MainWindow::on_pushButton_Settings_clicked()
{
    hide();
    settingWindow -> show();
}

// Close the main window and show the Player v Player window
void MainWindow::on_pushButton_PvP_clicked()
{
    emit startGame(PVP);
    hide();
    pvpWindow -> show();
}

// Close the main window and show the Player v RoboMate window
void MainWindow::on_pushButton_PvRM_clicked()
{
    emit startGame(PVE);
    //emit movePiece(3,11);
    hide();
    pvrmWindow -> show();
}


// Close the main window and show the Reset window
void MainWindow::on_pushButton_Reset_clicked()
{
    emit reset();
    hide();
    resetWindow -> show();

    // Send signal to Board that Reset button has been pushed

    // Receive signal from Board when pieces are back in place

    // When signal is received, go back to MainWindow:
    /*hide();
    if (auto mw = mainWindow.lock()) {
        mw->show();
    }
    emit closed();*/
}

