#include <QtGui/QApplication>
#include "./mainwindow.h"

using namespace Nightingale;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* mw = new MainWindow();
    mw->show();

    return a.exec();
}
