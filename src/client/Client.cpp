#include "./Client.h"
#include "./mainwindow.h"
#include "../../uic/ui_mainwindow.h"
#include "./roomwindow.h"
#include "../../uic/ui_roomwindow.h"
#include "../core/Socket.h"
#include "../core/Room.h"
#include "../core/Message.h"
#include "../core/ConnectionManager.h"

Client::Client(MainWindow * mw) : serverSocket_(new Socket(this)), mw_(mw) {
    chatRooms_ = new QMap<QString, Room *>();

    QObject::connect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                     this, SLOT(slotConnect()));
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

    if (this->connect(port, &host)) {
        mw_->getUi()->ipField->setReadOnly(true);
        mw_->getUi()->portField->setReadOnly(true);
        mw_->getUi()->nameField->setReadOnly(true);
        QObject::disconnect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                            this, SLOT(slotConnect()));
        QObject::connect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                         this, SLOT(addRoom()));

        addRoom();
    }
}

void Client::addRoom() {
    QString name = mw_->getUi()->roomField->text();
    if (QString::compare(name, tr("")) == 0) {
        name = tr("Chat Room");
    }

    if (!mw_->getRooms()->contains(name)) {
        initRoom(name);
    } else {
        mw_->getRooms()->value(name)->show();
    }
}

void Client::initRoom(QString name) {
    Room* room = new Room(name);
    RoomWindow* rw = new RoomWindow();

    room->addUser(QPair<QString, QString>
                 (tr("192.168.0.112"), mw_->getUi()->nameField->text()));

    chatRooms_->insert(room->getName(), room);

    QObject::connect(rw, SIGNAL(sendMessage(QString*, QString)),
                     this, SLOT(slotPrepMessage(QString*, QString)));

    mw_->getRooms()->insert(name, rw);
    mw_->getRooms()->value(name)->getUi()->rommName->setText(name);
    mw_->getRooms()->value(name)->setWindowTitle(name);
    QString username = chatRooms_->at(chatRooms_->size() - 1)->getUser(0).second;
    mw_->getRooms()->value(name)->getUi()->userList->addItem(username);
    mw_->getRooms()->value(name)->show();
}

void Client::sendUserList(Room room) {
    Message* message = new Message();
    message->setType(USR_LIST);
    message->setRoom(room.getName());
    //message->setSender(QPair<QString, QString>
    //               (tr("192.168.0.112"), mw_->getUi()->nameField->text()));

    QByteArray* msg = new QByteArray();
    QDataStream ds(msg, QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    ds << room.getUsers();
    message->setData(*msg);
    serverSocket_->write(message->serialize());
}

void Client::slotPrepMessage(QString * message, QString roomName) {
    qDebug() << "Msg tx: " << *message;

    // Messages are terminated with '\n'.
    *message += '\n';
    QByteArray data = message->toAscii();

    Message* msg = new Message();
    msg->setType(CHAT_MSG);
    msg->setRoom(roomName);
    foreach (Room* room, *chatRooms_) {
        if (QString::compare(room->getName(), roomName) == 0) {
            //msg->setSender(room->getUser(0));
        }
    }
    msg->setData(data);

    serverSocket_->write(msg->serialize());
}

void Client::slotDisplayMessage(QByteArray * data) {
    qDebug() << "Msg rx: ";// << *data;
    //QString message(*data);
    Message* msg = new Message();
    msg->deserialize(data);
    QString message(msg->getMessage());

    mw_->getRooms()->value(msg->getRoom())->getUi()
            ->roomLog->setFontWeight(QFont::Bold);
    mw_->getRooms()->value(msg->getRoom())->getUi()->roomLog
            ->append(msg->getSender().first
                     + tr(" - ") + msg->getSender().second);

    mw_->getRooms()->value(msg->getRoom())->getUi()
            ->roomLog->setFontWeight(QFont::Normal);
    mw_->getRooms()->value(msg->getRoom())->getUi()->roomLog->append(message);
}

void Client::updateUsers(QByteArray* buffer) {
    Message *message = new Message();
    message->deserialize(buffer);
    //int index = 0;
    QVector<QPair<QString, QString> > users(message->getUserList());
    //QListWidget* list = mw_->getRooms()->value(message->getRoom())
    //                   ->getUi()->userList;
    //QString username(mw_->getUi()->nameField->text());

    foreach (Room* room, *chatRooms_) {
        if (QString::compare(room->getName(), message->getRoom()) == 0) {
            if (room->getUsers()->size() != users.size()) {
                mw_->getRooms()->value(message->getRoom())->getUi()
                        ->userList->clear();
                QVectorIterator<QPair<QString, QString> > i(users);
                while (i.hasNext()) {
                    room->addUser(i.next());
                }/*
                foreach (QPair<QString, QString> user, users) {
                    room->addUser(user);
                }*/
                QVectorIterator<QPair<QString, QString> > k(users);
                while (k.hasNext()) {
                    mw_->getRooms()->value(message->getRoom())->getUi()
                            ->userList->addItem(k.next().second);
                }/*
                foreach (QPair<QString, QString> user, users) {
                    mw_->getRooms()->value(message->getRoom())->getUi()
                            ->userList->append(user.second);
                }*/
            }
        }
    }
}
