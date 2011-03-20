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

bool Client::connect(int port, QString * host) {
    return serverSocket_->connect(port, host->toAscii().constData());
}

void Client::slotConnect() {
    QString host = mw_->getUi()->ipField->text();
    int port = mw_->getUi()->portField->text().toInt();
    QString name = mw_->getUi()->roomField->text();

    if (this->connect(port, &host)) {
        mw_->getUi()->ipField->setReadOnly(true);
        mw_->getUi()->portField->setReadOnly(true);
        mw_->getUi()->nameField->setReadOnly(true);
        QObject::disconnect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                   this, SLOT(slotConnect()));
        QObject::connect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                this, SLOT(addRoom()));

        RoomWindow* rw = new RoomWindow();
        rw->getUi()->sendArea->installEventFilter(rw);

        QObject::connect(rw, SIGNAL(sendMessage(QString*)),
                         this, SLOT(slotPrepMessage(QString*)));

        mw_->getRooms()->insert(name, rw);
        mw_->getRooms()->value(name)->show();
    }
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
    mw_->getRooms()->value(tr(""))->getUi()->roomLog->append(message);
}

void Client::addRoom() {
    QString name = mw_->getUi()->roomField->text();
    if (!mw_->getRooms()->contains(name)) {
        RoomWindow* rw = new RoomWindow();
        rw->getUi()->sendArea->installEventFilter(rw);

        QObject::connect(rw, SIGNAL(sendMessage(QString*)),
                         this, SLOT(slotPrepMessage(QString*)));

        mw_->getRooms()->insert(name, rw);
        mw_->getRooms()->value(name)->show();
    } else {
        mw_->getRooms()->value(name)->show();
    }
}
