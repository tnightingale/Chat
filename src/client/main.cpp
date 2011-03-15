#include <QtGui/QApplication>
#include "./mainwindow.h"
#include "./Client.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow * mw = new MainWindow();
    Client * client = new Client(mw);
    
    mw->show();

    return a.exec();
}
