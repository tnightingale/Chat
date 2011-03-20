#include "Server.h"
#include "../core/Socket.h"
#include "../core/User.h"
#include "../core/Room.h"
#include "../core/Message.h"

Server::Server()
: listenSock_(new Socket(this)), users_(new QMap<int, User *>()),
  rooms_(new QMap<QString, Room * >()) {}

Server::~Server() {
    delete listenSock_;

    // Cleaning up rooms objects.
    foreach (Room * room, *rooms_) {
        delete room;
    }
    delete rooms_;

    // Cleaning up users objects.
    foreach (User * user, *users_) {
        delete user;
    }
    delete users_;
}

void Server::listen(int port) {
    port_ = port;
    listenSock_->listen(port);
}

void Server::slotNewUser(int socketDescriptor, char * address) {
    User * user = new User(address);
    user->setSocketD(socketDescriptor);
    users_->insert(socketDescriptor, user);
}

void Server::slotUserDisconnected(int socketDiscriptor) {
    User * user = users_->take(socketDiscriptor);
    delete user;
}

void Server::forwardMessage(User * sender, Message * msg) {
    QSet<User *> recipients = rooms_->value(msg->getRoom())->getUsers();
    QSet<int> * recipientDs = new QSet<int>();

    foreach (User * user, recipients) {
        if (user->getSocketD() == sender->getSocketD()) {
            continue;
        }
        recipientDs->insert(user->getSocketD()); 
    }

    emit bcstMsg(msg->serialize(), recipientDs);
}

void Server::userJoinRoom(User * sender, Message * msg) {
    QString roomName(msg->getMessage());
    Room * room = NULL;
    if ((room = rooms_->value(roomName)) == 0) {
        room = new Room(roomName);
        rooms_->insert(roomName, room);
    }
    room->addUser(sender);

    Message * userList = new Message();
    userList->setType(MSG_USERLIST);
    userList->setRoom(roomName);
    userList->setData(prepareUserList(room->getUsers()));
    forwardMessage(NULL, userList);
}

QByteArray Server::prepareUserList(QSet<User *> users) {
    QVector<QString> userVector = QVector<QString>();
    QByteArray* userList = new QByteArray();
    QDataStream ds(userList, QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    foreach (User * user, users) {
        userVector.append(user->toString());
    } 
    ds << userVector;
    return *userList;
}

void Server::slotMessageRx(int userSD, QByteArray * buffer) {
    Message * msg = new Message(buffer);
    User * sender = users_->value(userSD);

    msg->setSender(sender);
    switch (msg->getType()) {
        case MSG_USERLIST:
        //emit userListReceived(msg->serialize());
            break;

        case MSG_JOINROOM:
            userJoinRoom(sender, msg);
            break;

        case MSG_CHAT:
            forwardMessage(sender, msg);
            break;

        default:
          // Shouldn't get here.
          break;
    }
}
