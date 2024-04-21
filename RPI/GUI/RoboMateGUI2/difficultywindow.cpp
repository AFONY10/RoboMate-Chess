#include "difficultywindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>
#include <iostream>
#include <QDebug>

// Headers for andre vinduer
#include "settingwindow.h"

// Constructor for the difficulty window
DifficultyWindow::DifficultyWindow(QWidget *parent)
    : QDialog(parent)
{
    m_layout = new QVBoxLayout(this);

    // Header Label
    QLabel *headerLabel = new QLabel("Choose the difficulty, 1-40", this);
    m_layout->addWidget(headerLabel);

    // Slider and Text Edit (Centered)
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setMinimum(MIN_VALUE);
    m_slider->setMaximum(MAX_VALUE * STEPS);
    m_textEdit = new QLineEdit(this);

    QHBoxLayout *sliderLayout = new QHBoxLayout;
    sliderLayout->addStretch(); // Push slider and text edit to the center
    sliderLayout->addWidget(m_slider);
    sliderLayout->addWidget(m_textEdit);
    sliderLayout->addStretch();
    m_layout->addLayout(sliderLayout);
    connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(updateTextOnSliderChange(int)));

    // "Go Back" Button (Far Left)
    m_goBackButton = new QPushButton("Go Back", this);
    connect(m_goBackButton, SIGNAL(clicked()), this, SLOT(goBackButton()));

    // "Save" Button (Far Right)
    m_saveButton = new QPushButton("Save", this);
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(saveButton()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_goBackButton);
    buttonLayout->addStretch(); // Push save button to the far right
    buttonLayout->addWidget(m_saveButton);
    m_layout->addLayout(buttonLayout);

    // Set the slider and text edit to the saved values
    m_slider->setValue(savedSliderValue);
    m_textEdit->setText(savedTextEditValue);

    setLayout(m_layout);
    setFixedSize(650, 400);
}

// Destructor for the difficulty window
DifficultyWindow::~DifficultyWindow() {}

// Show the difficulty window
void DifficultyWindow::showDifficultyWindow(){
    show();
}

// Update the text edit when the slider is dragged
void DifficultyWindow::updateTextOnSliderChange(int position) {
    float positionF = position / float(STEPS);
    m_textEdit->setText(QString::number(positionF));
}

// Close the difficulty window
void DifficultyWindow::goBackButton() {
    hide();
       if (auto sw = settingWindow.lock()) {
           sw->show();
       }

    emit closed();
}

// Save the difficulty and close the difficulty window
void DifficultyWindow::saveButton() {
    // Store the current slider and text edit values
    savedSliderValue = m_slider->value();
    savedTextEditValue = m_textEdit->text();

    // Print the current slider value to the console
    qDebug() << "Slider value saved:" << savedSliderValue;
    qDebug() << "Slider value saved:" << savedTextEditValue;

    // Emit saved value to Board class
    emit setDifficulty(savedSliderValue);
}

