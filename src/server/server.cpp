#include "Server.h"
#include "../core/Socket.h"
#include "../core/User.h"

Server::Server() : listenSock_(new Socket()), users_(new QMap<int, User *>()) {}

Server::~Server() {
    delete listenSock_;

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
