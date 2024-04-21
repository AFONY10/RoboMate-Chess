#ifndef PVPWINDOW_H
#define PVPWINDOW_H

#include <QDialog>
#include <memory>
#include "../../Board.h"

// Forward decleration så der ikke kommer cirkulær inklusion
class MainWindow;

namespace Ui {
class PvPWindow;
}

class PvPWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PvPWindow(QWidget *parent = nullptr);
    ~PvPWindow();

signals:
    void closed(); // Signal to notify the closure of this window
    void finished();
    void giveUp();
public slots:
    void showPvPWindow(); // Slot to display the Start game player window again
    void setTurn(Color color);
    void showIllegalMove();

    void showQueenPromotion(Color color );
    void showCheckmate(Color color);
    void showStalemate();
private slots:

    void on_pushButton__giveUp_clicked();

    void on_pushButton_goBack_clicked();
    void on_pushButton_actionCompleted_clicked();

private:
    Ui::PvPWindow *ui;
    std::weak_ptr<MainWindow> mainWindow;
    bool isWhiteTurn_;
};

#endif // PVPWINDOW_H
