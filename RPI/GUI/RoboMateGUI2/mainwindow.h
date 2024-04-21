#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QSerialPort>
#include "../../Board.h"
#include "uart.h"

// Forward decleration så der ikke kommer cirkulær inklusion
class PvPWindow;
class SettingWindow;
class PvRMWindow;
class ResetWindow;
class GameLoopThread;
class Board;
class DifficultyWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void closed(); // Signal to notify the closure of this window
    void startGame(Gamemode gm);
    void reset();

public slots:
    void showMainWindow(); // Slot to display the main window again

private slots:

    void on_pushButton_Settings_clicked();

    void on_pushButton_PvP_clicked();

    void on_pushButton_PvRM_clicked();

    void on_pushButton_Reset_clicked();

private:
    Board* board_;
    UART* uart_;
    //GameLoopThread* thread_;
    Ui::MainWindow *ui;
    std::unique_ptr<PvPWindow> pvpWindow;
    std::unique_ptr<SettingWindow> settingWindow;
    std::unique_ptr<PvRMWindow> pvrmWindow;
    std::unique_ptr<ResetWindow> resetWindow;
    std::unique_ptr<DifficultyWindow> difficultyWindow;
};
#endif //MAINWINDOW_H
