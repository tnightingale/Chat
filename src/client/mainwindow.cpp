#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "../core/Socket.h"

using namespace Nightingale;

MainWindow::MainWindow(QWidget *parent) 
  : QMainWindow(parent), ui(new Ui::MainWindow) {

    Socket* s = new Socket();
    ui->setupUi(this);
    s->listen(7000);
}

MainWindow::~MainWindow() {
    delete ui;
}
