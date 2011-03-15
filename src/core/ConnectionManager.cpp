#include "ConnectionManager.h"
#include "Socket.h"

ConnectionManager::ConnectionManager(int listenSocketD) {
    listenSocketD_ = listenSocketD;
    maxfd_ = listenSocketD;

    clients_ = new QMap<int, Socket *>();

    FD_ZERO(&allset_);
    FD_SET(listenSocketD_, &allset_);
}

ConnectionManager::~ConnectionManager() {
    foreach (Socket * clientSock, *clients_) {
        int socket = clientSock->getSocketD();
        FD_CLR(socket, &allset_);
        close(socket);
        delete clientSock;
    }
}

void ConnectionManager::start() {
    fd_set rset;
    int nready = 0;

    while (TRUE) {
        rset = allset_;
        nready = select(maxfd_ + 1, &rset, NULL, NULL, NULL);

        // 1st check to see if there are any new connections.
        if (FD_ISSET(listenSocketD_, &rset)) {
            // New client connection.
            this->accept();

            if (--nready <= 0) {
                // No more readable descriptors
                continue;
            }
        }

        // 2nd check all client connections for data.
        foreach (Socket * socket, *clients_) {

            // If socket is not flagged, skip it.
            if (!FD_ISSET(socket->getSocketD(), &rset)) {
                continue;
            }

            // Data received, process socket.
            qDebug("ConnectionManager::start(); (%d) Message received.", 
                socket->getSocketD());
            this->process(socket); 


            // If no more flagged sockets, break out of loop. 
            if (--nready <= 0) {
                break;
            }
        }
    }

}

void ConnectionManager::accept() {
    int newSD = 0;
    Socket * newSocket = NULL;
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Set up client socket.
    if ((newSD = ::accept(listenSocketD_, (struct sockaddr *) &client_addr, 
            &client_len)) == -1) {
        qDebug("ConnectionManager::start(); Accept error.");
    }

    newSocket = new Socket(newSD);
    clients_->insert(newSD, newSocket);

    emit newConnection(newSD, inet_ntoa(client_addr.sin_addr));

    if (clients_->size() == FD_SETSIZE) {
        qDebug("ConnectionManager::start(); Too many clients.");
        return;
    }

    // Add new descriptor to set.
    FD_SET(newSD, &allset_);
    if (newSD > maxfd_) {
        maxfd_ = newSD;
    }
}

void ConnectionManager::process(Socket * socket) {
    QByteArray * buffer = new QByteArray();
    int socketD = socket->getSocketD();

    // Read from socket into buffer.
    if(socket->read(buffer) == 0) {
        // connection closed by client

        emit closedConnection(socketD);

        FD_CLR(socketD, &allset_);
        clients_->remove(socketD);
        delete socket;
    }

    // Do stuff with received data here.
    qDebug() << buffer->constData();
}
