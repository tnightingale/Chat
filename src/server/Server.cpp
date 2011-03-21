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
    QSet<User *> * recipients(rooms_->value(msg->getRoom())->getUsers());

    foreach (User * user, *recipients) {
        if (sender != NULL && user->getSocketD() == sender->getSocketD()) {
            continue;
        }

        // TODO: This was supposed to be encapsulated by the Socket class. 
        QByteArray * buffer = msg->serialize();
        const char * bp = buffer->constData();
        ::write(user->getSocketD(), bp, buffer->size());
    }
}

void Server::userJoinRoom(User * sender, Message * msg) {
    QString roomName(msg->getRoom());
    Room * room = NULL;

    if ((room = rooms_->value(roomName)) == 0) {
        room = new Room(roomName);
        rooms_->insert(roomName, room);
        qDebug("Server::userJoinRoom(); Room created (%s)", roomName.toAscii().data());
    }
    room->addUser(sender);

    broadcastUserList(room);
}

void Server::userLeaveRoom(User * sender, Message * msg) {
    QString roomName(msg->getRoom());
    Room * room = NULL;

    room = rooms_->value(roomName);
    room->removeUser(sender);

    // If no more people in room, destroy it.
    if (room->getUsers()->count() == 0) {
        rooms_->remove(roomName);
        delete room;
    } 
    
    // Otherwise notify everyone remaining of changes.
    else {
        broadcastUserList(room);
    }
}

void Server::broadcastUserList(Room * room) {
    Message * userList = new Message();

    userList->setType(MSG_USERLIST);
    userList->setRoom(room->getName());
    userList->setData(prepareUserList(room->getUsers()));

    forwardMessage(NULL, userList);
}

QByteArray Server::prepareUserList(QSet<User *> * users) {
    QString userString;
    QTextStream ts(&userString);

    foreach (User * user, *users) {
        ts << *user << ",";
    } 

    qDebug() << "Server::prepareUserList(); " << userString.toAscii();

    return userString.toAscii();
}

void Server::userSetNick(User * sender, Message * msg) {
    QString newName(msg->getMessage());
    sender->setUserName(newName);

    // TODO: This will update the user's name globally but only notify the 
    //       user's current room. Others will eventually get updated.
    if (msg->getRoom() != "") {
        broadcastUserList(rooms_->value(msg->getRoom()));
    }
}

void Server::slotMessageRx(int userSD, QByteArray * buffer) {
    Message * msg = new Message(buffer);
    User * sender = users_->value(userSD);

    msg->setSender(sender);
    switch (msg->getType()) {

        case MSG_JOINROOM:
            userJoinRoom(sender, msg);
            break;

        case MSG_LEAVEROOM:
            userLeaveRoom(sender, msg);
            break;

        case MSG_CHAT:
            forwardMessage(sender, msg);
            break;

        case MSG_SETNICK:
            userSetNick(sender, msg);
            break;

        default:
          // Shouldn't get here.
          break;
    }
}
