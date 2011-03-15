#include "roomwindow.h"
#include "ui_roomwindow.h"

RoomWindow::RoomWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomWindow) {
    ui->setupUi(this);
}

RoomWindow::~RoomWindow() {
    delete ui;
}
