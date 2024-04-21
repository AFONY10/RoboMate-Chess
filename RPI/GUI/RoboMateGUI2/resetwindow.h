#ifndef RESETWINDOW_H
#define RESETWINDOW_H

#include <QDialog>

// Forward decleration
class MainWindow;

namespace Ui {
class ResetWindow;
}

class ResetWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResetWindow(QWidget *parent = nullptr);
    ~ResetWindow();

signals:
    void closed(); // Signal to notify the closure of this window

public slots:
    void showResetWindow(); // Slot to display the setting window again

private slots:
    void on_pushButton_goBack_clicked();

private:
    Ui::ResetWindow *ui;
    std::weak_ptr<MainWindow> mainWindow;
};

#endif // RESETWINDOW_H
