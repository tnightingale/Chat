#include <QtGui/QApplication>
#include "./mainwindow.h"
#include "./Client.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Client * client = new Client();

    MainWindow * mw = new MainWindow();
    mw->show();

    return a.exec();
}
