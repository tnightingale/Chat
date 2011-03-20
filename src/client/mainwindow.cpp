#include "./roomwindow.h"
#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_roomwindow.h"

MainWindow::MainWindow(QWidget *parent) 
  : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    rooms = new QMap<QString, RoomWindow*>();

    ui->connectButton->setEnabled(TRUE);
}

MainWindow::~MainWindow() {
    delete ui;
    delete rooms;
}
