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
        setNick(mw_->getUi()->nameField->text());

        mw_->getUi()->ipField->setReadOnly(true);
        mw_->getUi()->portField->setReadOnly(true);
        mw_->getUi()->nameField->setReadOnly(true);
        QObject::disconnect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                            this, SLOT(slotConnect()));
        QObject::connect(mw_->getUi()->connectButton, SIGNAL(clicked()),
                         this, SLOT(addRoom()));

        joinRoom(mw_->getUi()->roomField->text());
        
    }
}

void Client::joinRoom(QString roomName) {
    if (QString::compare(roomName, tr("")) == 0) {
        roomName = tr("Chat Room");
    }

    if ((chatRooms_->value(roomName)) != 0) {
        // Already a member of requested room.
        mw_->getRooms()->value(roomName)->show();
        return;
    }

    Message * request = new Message();

    request->setType(MSG_JOINROOM);
    request->setRoom(roomName);

    serverSocket_->write(request->serialize());
}

void Client::setNick(QString name) {
    Message * request = new Message();
    request->setType(MSG_SETNICK);
    request->setData(name.toAscii());

    serverSocket_->write(request->serialize());
}

void Client::addRoom() {
    joinRoom(mw_->getUi()->roomField->text());
}

/*
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

    //QString username = chatRooms_->at(chatRooms_->size() - 1)->getUser(0).second;

    //mw_->getRooms()->value(name)->getUi()->userList->addItem(username);
    //mw_->getRooms()->value(name)->show();
}
*/

void Client::sendUserList(Room room) {
    Message* message = new Message();
    message->setType(MSG_USERLIST);
    message->setRoom(room.getName());
    //message->setSender(QPair<QString, QString>
    //               (tr("192.168.0.112"), mw_->getUi()->nameField->text()));

    QByteArray* msg = new QByteArray();
    QString userString("");
    QDataStream ds(msg, QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_4_7);

    foreach (User * user, *(room.getUsers())) {
        userString.append(user->toString() + tr(","));
    }

    ds << userString;
    message->setData(*msg);
    serverSocket_->write(message->serialize());
}

void Client::slotPrepMessage(QString * message, QString roomName) {
    // Messages are terminated with '\n'.
    *message += '\n';
    QByteArray data = message->toAscii();

    Message* msg = new Message();
    msg->setType(MSG_CHAT);
    msg->setRoom(roomName);
    foreach (Room* room, *chatRooms_) {
        if (QString::compare(room->getName(), roomName) == 0) {
            //msg->setSender(room->getUser(0));
        }
    }
    msg->setData(data);

    serverSocket_->write(msg->serialize());
    displayMessage(msg);
}

void Client::displayMessage(Message * msg) {
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

void Client::rxUserList(Message * msg) {
    QString roomName(msg->getRoom());
    Room * room = NULL;

    if ((room = chatRooms_->value(msg->getRoom())) == 0) {
        // Room doesn't exist, create it.
        room = new Room(roomName);
        chatRooms_->insert(roomName, room);

        RoomWindow * rw = new RoomWindow(roomName);
        QObject::connect(rw, SIGNAL(sendMessage(QString*, QString)),
                         this, SLOT(slotPrepMessage(QString*, QString)));
        mw_->getRooms()->insert(roomName, rw);
        rw->show();
    }

    // Update user list here.
}

void Client::slotMessageRx(int, QByteArray * data) {
    qDebug() << "Msg rx: " << data;

    Message* msg = new Message(data);

    switch (msg->getType()) {
        case MSG_CHAT:
            displayMessage(msg);
            break;
        
        case MSG_USERLIST:
            // Received a room user list request.
            // - If room doesn't exist, now is a good time to create it & its 
            //   window.
            // - Otherwise just update the existing rooms userlist.
            rxUserList(msg);
            break;

        default:
            // No go here.
            break;
    }
}

void Client::updateUsers(QByteArray* buffer) {
    Message *message = new Message();
    message->deserialize(buffer);
    QString users(message->getUserList());
    QSet<User*> userList = QSet<User*>();

    int mid = 0;
    QStringList userStrings = users.split(tr(","), QString::SkipEmptyParts);
    foreach (QString userString, userStrings) {
        mid = userString.indexOf(tr("@"));
        User* newUser = new User(userString.right(mid).toAscii().data());
        userList.insert(newUser);
    }

    QSetIterator<User*> newUser(userList);
    while (newUser.hasNext()) {
        chatRooms_->value(message->getRoom())->addUser(newUser.next());
    }
}
