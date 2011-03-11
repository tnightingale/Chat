#include "ConnectionManager.h"

using namespace Nightingale;

ConnectionManager::ConnectionManager(int listenSocketD) {
    listenSocketD_ = listenSocketD;
    maxfd_ = listenSocketD;
    maxi_ = -1; // This could possibly be removed.
    for (int i = 0; i < FD_SETSIZE; i++) {
        clients_[i] = -1; // -1 indicates available entry
    }

    FD_ZERO(&allset_);
    FD_SET(listenSocketD_, &allset_);
}

ConnectionManager::~ConnectionManager() {
    for (int i = 0; i < maxi_; i++) {
        FD_CLR(clients_[i], &allset_);
        close(clients_[i]);
    }
}

void ConnectionManager::start() {
    fd_set rset;
    int nready = 0;

    while (TRUE) {
        rset = allset_;
        nready = select(maxfd_ + 1, &rset, NULL, NULL, NULL);

        // New client connection.
        if (FD_ISSET(listenSocketD_, &rset)) {
            this->accept();

            if (--nready <= 0) {
                // No more readable descriptors
                continue;
            }
        }

        // Aman's code continues here.
    }


}

void ConnectionManager::accept() {
    int i = 0;
    int newSD = 0;
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Set up client socket.
    if ((newSD = ::accept(listenSocketD_, (struct sockaddr *) &client_addr, 
            &client_len)) == -1) {
        qDebug("ConnectionManager::start(); Accept error.");
    }

    emit newConnection(newSD);

    qDebug("ConnectionManager::start(); Remote Address:  %s.", 
        inet_ntoa(client_addr.sin_addr));

    for (i = 0; i < FD_SETSIZE; i++) {
        if (clients_[i] < 0) {
            clients_[i] = newSD; // save descriptor
            break;
        }
    }

    if (i == FD_SETSIZE) {
        qDebug("ConnectionManager::start(); Too many clients.");
        return;
    }

    // Add new descriptor to set.
    FD_SET(newSD, &allset_);
    if (newSD > maxfd_) {
        maxfd_ = newSD;
    }

    if (i > maxi_) {
        // new max index in client[] array
        maxi_ = i; 
    }
}
