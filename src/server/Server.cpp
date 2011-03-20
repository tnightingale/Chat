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
    users_->insert(socketDescriptor, user);
}

//void Server::slotJoinRoom(

void Server::slotUserDisconnected(int socketDiscriptor) {
    User * user = users_->take(socketDiscriptor);
    delete user;
}

void Server::slotMessageRx(QByteArray * buffer) {
    Message * msg = new Message(buffer);

    switch (msg->getType()) {
        case USR_LIST:
        //emit userListReceived(msg->serialize());
          break;

        case CHAT_MSG:
          rooms_->value(msg->getRoom())->newMessage(msg);
          break;

        default:
          // Shouldn't get here.
          break;
    }
}
