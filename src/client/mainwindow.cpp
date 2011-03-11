#include "./roomwindow.h"
#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "../core/Socket.h"

MainWindow::MainWindow(QWidget *parent) 
  : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    rw = new RoomWindow();
    ui->connectButton->setEnabled(TRUE);
    connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(connectRoom()));
}

void MainWindow::connectRoom() {

    rw->show();

    s = new Socket();
    s->listen(7000);
}

MainWindow::~MainWindow() {
    delete ui;
    delete rw;
}
