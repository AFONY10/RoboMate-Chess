# RoboMate

## Description

RoboMate is an automated chess game application/system developed by 8 3rd-semester students from the University of Aarhus, majoring in Software Technology and Electrical Engineering (4 of each major). 
It is essentially a Raspberry Pi software implementation with a graphical user interface (GUI), engine/API, and game logic (Made in Qt-Creator). 
The system utilizes UART communication to establish a connection from the Raspberry Pi to a PSoC microcontroller, facilitating the integration with physical hardware devices such as an XY-Plotter and a self-built sensor/LED chessboard.

## Features

- Player vs. player (PvP) mode
- Player vs. AI (RoboMate) mode with adjustable difficulty levels
- Customizable settings including player color selection
- Graphical representation of the chessboard and pieces
- Legal move highlighting
- Support for detecting checkmate and stalemate
- Queen promotion functionality
- Integration with physical hardware devices via UART communication

## Installation

To run the chess game and RoboMate integration, follow these steps:

1. Clone this repository to your local machine.
2. Make sure you have the Qt framework installed on your system.
3. Open the project in Qt Creator.
4. Build the project and run the executable.

## Usage

- Upon launching the application, you will be presented with a main menu.
- From the main menu, you can start a new game, adjust settings, or exit the application.
- During gameplay, make moves by selecting a piece and then selecting its destination square.
- The game will automatically detect checkmate or stalemate conditions and end the game accordingly.
- In player vs. AI mode, the AI opponent (RoboMate) will make its moves automatically.

## Dependencies

- Qt framework (version X.X.X)
- C++ compiler with C++11 support

## Contributing

Contributions to this project are welcome. You can contribute by:

- Reporting bugs
- Adding new features
- Improving the existing codebase
- Writing tests

Before making significant changes, please open an issue to discuss the proposed changes.


## Authors

- [Anthony Nguyen (AFONY10)](https://github.com/AFONY10)
- Contact Anthony for information about the other group members or the project itself.

