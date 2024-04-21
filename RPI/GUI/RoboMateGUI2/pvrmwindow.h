#ifndef PVRMWINDOW_H
#define PVRMWINDOW_H

#include <QDialog>
#include <memory>
#include "../../Board.h"
// #include "uart.h"

// Forward decleration så der ikke kommer cirkulær inklusion
class MainWindow;

namespace Ui {
class PvRMWindow;
}

class PvRMWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PvRMWindow(QWidget *parent = nullptr);
    ~PvRMWindow();

signals:
    void closed(); // Signal to notify the closure of this window
    void finished();
    void giveUp();
    void movePiece(int fromPos, int toPos);
public slots:
    void showPvRMWindow(); // Slot to display the Start game player window again
    void setTurn(Color color);
    void showIllegalMove();

    void showQueenPromotion(Color color );
    void showCheckmate(Color color);
    void showStalemate();
private slots:
    void on_pushButton__giveUp_clicked();
    void on_pushButton_actionCompleted_clicked();
    void on_pushButton_goBack_clicked();

    void on_pushButton_sendUart_clicked();

    void on_pushButton_e5_clicked();

private:
    //UART* uart_;
    Ui::PvRMWindow *ui;
    std::weak_ptr<MainWindow> mainWindow;
    bool isWhiteTurn_;
};

#endif // PVRMWINDOW_H
