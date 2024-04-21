QT += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../Board.cpp \
    ../../Chess_engine.cpp \
    ../../Piece.cpp \
    ../../Pieces/Bishop.cpp \
    ../../Pieces/King.cpp \
    ../../Pieces/Knight.cpp \
    ../../Pieces/Pawn.cpp \
    ../../Pieces/Queen.cpp \
    ../../Pieces/Rook.cpp \
    colourwindow.cpp \
    difficultywindow.cpp \
    main.cpp \
    mainwindow.cpp \
    pvpwindow.cpp \
    pvrmwindow.cpp \
    resetwindow.cpp \
    settingwindow.cpp \
    uart.cpp

HEADERS += \
    ../../Board.h \
    ../../Chess_engine.h \
    ../../Piece.h \
    ../../Pieces/Bishop.h \
    ../../Pieces/King.h \
    ../../Pieces/Knight.h \
    ../../Pieces/Pawn.h \
    ../../Pieces/Queen.h \
    ../../Pieces/Rook.h \
    ../../subprocess.h \
    colourwindow.h \
    difficultywindow.h \
    gameloopthread.h \
    mainwindow.h \
    pvpwindow.h \
    pvrmwindow.h \
    resetwindow.h \
    settingwindow.h \
    uart.h

FORMS += \
    colourwindow.ui \
    difficultywindow.ui \
    mainwindow.ui \
    pvpwindow.ui \
    pvrmwindow.ui \
    resetwindow.ui \
    settingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
