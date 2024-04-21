#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <memory>
#include "../../Board.h"

class MainWindow;
class DifficultyWindow;
class ColourWindow;

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

signals:
    void closed(); // Signal to notify the closure of this window
    void setPlayerColor(Color color);
    void setDifficulty(int dif);

public slots:
    void showSettingWindow(); // Slot to display the setting window again
    void setColor(Color color);

private slots:
    void on_pushButton_difficulty_clicked();

    void on_pushButton_colour_clicked();

    void on_pushButton_goBack_clicked();
    void putDifficulty(int dif);

private:
    Ui::SettingWindow *ui;
    std::weak_ptr<MainWindow> mainWindow;
    std::unique_ptr<DifficultyWindow> difficultyWindow;
    std::unique_ptr<ColourWindow> colourWindow;
};

#endif // SETTINGWINDOW_H
