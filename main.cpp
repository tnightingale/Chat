#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Nightingale::MainWindow w;
    w.show();

    return a.exec();
}
