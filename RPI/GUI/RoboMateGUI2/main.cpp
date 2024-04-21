#include "mainwindow.h"
#include "pvpwindow.h"
#include "settingwindow.h"
//#include "difficultywindow.h"
#include "../../Board.h"

#include <QApplication>

// Main function
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
