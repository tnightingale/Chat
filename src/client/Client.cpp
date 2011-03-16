#include "./Client.h"
#include "./mainwindow.h"
#include "../../uic/ui_mainwindow.h"
#include "./roomwindow.h"
#include "../../uic/ui_roomwindow.h"
#include "../core/Socket.h"

Client::Client(MainWindow * mw) : serverSocket_(new Socket(this)), mw_(mw) {
    QObject::connect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                     this, SLOT(slotConnect()));
    
    QObject::connect(mw_, SIGNAL(sendMessage(QString *)),
                     this, SLOT(slotPrepMessage(QString *)));
}

Client::~Client() {
    delete serverSocket_;
}

void Client::connect(int port, QString * host) {
    serverSocket_->connect(port, host->toAscii().constData());
}

void Client::slotConnect() {
    QString host = mw_->getUi()->ipField->text();
    int port = mw_->getUi()->portField->text().toInt();

    this->connect(port, &host);
}

void Client::slotPrepMessage(QString * message) {
    qDebug() << "Msg tx: " << *message;

    // Messages are terminated with '\n'.
    *message += '\n';
    QByteArray data = message->toAscii();
    serverSocket_->write(&data);
}

void Client::slotDisplayMessage(QByteArray * data) {
    qDebug() << "Msg rx: " << *data;
    QString message(*data);
    mw_->getRW()->getUi()->roomLog->append(message);
}
