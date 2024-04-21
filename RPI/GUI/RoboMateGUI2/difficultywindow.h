#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QDialog>
#include <memory>
#include "../../Board.h"

class QVBoxLayout;
class QHBoxLayout; // Include QHBoxLayout for button arrangement
class QSlider;
class QLineEdit;
class QPushButton;

class SettingWindow;

class DifficultyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DifficultyWindow(QWidget *parent = nullptr);
    ~DifficultyWindow();

signals:
    void closed(); // Signal to notify the closure of this window
    void setDifficulty(int dif);

public slots:
    void showDifficultyWindow(); // Slot to display the main window again

private slots:
    void updateTextOnSliderChange(int position);
    void goBackButton();
    void saveButton(); // Slot for saving the slider setting

private:
    QVBoxLayout *m_layout;
    QSlider *m_slider;
    QLineEdit *m_textEdit;
    QPushButton *m_goBackButton;
    QPushButton *m_saveButton;
    std::weak_ptr<SettingWindow> settingWindow;

    const int MIN_VALUE = 1;
    const int MAX_VALUE = 40;
    const int STEPS = 1;

    int sliderValue; // Add a member variable to store the slider value
    int savedSliderValue; // Add a member variable to store the saved slider value
    QString savedTextEditValue;  // Add a member variable to store the saved text edit value


};

#endif // DIFFICULTYWINDOW_H
