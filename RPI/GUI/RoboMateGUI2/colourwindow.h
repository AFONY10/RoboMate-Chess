#ifndef COLOURWINDOW_H
#define COLOURWINDOW_H

#include <QDialog>
#include <memory>
#include "../../Board.h"

class QVBoxLayout;
class QHBoxLayout; // Include QHBoxLayout for button arrangement
//class QSlider;
//class QLineEdit;
//class QPushButton;
class SettingWindow;



namespace Ui {
class ColourWindow;
}

class ColourWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ColourWindow(QWidget *parent = nullptr);
    ~ColourWindow();
signals:
    void closed(); // Signal to notify the closure of this window
    void setColor(Color color);

public slots:
    void showColourWindow(); // Slot to display the main window again
private slots:
    void on_pushButton_goBack_clicked();

    void on_pushButton_white_clicked();

    void on_pushButton_black_clicked();

private:
    Ui::ColourWindow *ui;
    std::weak_ptr<SettingWindow> settingWindow;
    // SettingWindow* settingWindow;
};

#endif // COLOURWINDOW_H
