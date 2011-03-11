#include "ConnectionManager.h"

using namespace Nightingale;

ConnectionManager::ConnectionManager(int socketD) 
  : listen_sd_(socketD), maxfd_(socketD), maxi_(-1) {

    for (int i = 0; i < FD_SETSIZE; i++) {
        clients_[i] = -1; // -1 indicates available entry
    }

    FD_ZERO(&allset_);
    FD_SET(listen_sd_, &allset_);
}

void ConnectionManager::start() {
    int i = 0;
    int nready = 0;
    int new_sd = 0;
    fd_set rset;
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (TRUE) {
        rset = allset_;
        nready = select(maxfd_ + 1, &rset, NULL, NULL, NULL);

        // New client connection.
        if (FD_ISSET(listen_sd_, &rset)) {

            if ((new_sd = accept(listen_sd_, (struct sockaddr *) &client_addr, 
                    &client_len)) == -1) {
                qDebug("ConnectionManager::start(); Accept error.");
            }

            qDebug("ConnectionManager::start(); Remote Address:  %s.", 
                inet_ntoa(client_addr.sin_addr));

            for (i = 0; i < FD_SETSIZE; i++) {
                if (clients_[i] < 0) {
                    clients_[i] = new_sd; // save descriptor
                    break;
                }
            }

            if (i == FD_SETSIZE) {
                qDebug("ConnectionManager::start(); Too many clients.");
                exit(1);
            }

            // Add new descriptor to set.
            FD_SET(new_sd, &allset_);
            if (new_sd > maxfd_) {
                maxfd_ = new_sd;
            }

            if (i > maxi_) {
                // new max index in client[] array
                maxi_ = i; 
            }

            if (--nready <= 0) {
                // no more readable descriptors
                continue;
            }
        }

        // Aman's code continues here.
    }


}
