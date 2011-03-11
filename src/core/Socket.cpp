#include "Socket.h"
#include "ConnectionManager.h"

using namespace Nightingale;

Socket::Socket() {
    if ((socket_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw "Socket::Socket(); Could not create socket.";
    }

}

Socket::~Socket() {
    delete cm_;

    if (cThread_ != NULL) {
        cThread_->quit();
        delete cThread_;
    }

    close(socket_);
}

void Socket::listen(int port) {
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(socket_, (sockaddr *) &server, sizeof(server)) == -1) {
      //SystemFatal("bind error");
      qDebug("Socket::listen(); Could not bind listening socket.");
    }

    // Listen for connections
    ::listen(socket_, 5);
    
    ConnectionManager * cm = new ConnectionManager(socket_);
    cThread_ = new QThread();
    connect(cThread_, SIGNAL(started()),
            cm, SLOT(start()));
    cm->moveToThread(cThread_);

    cThread_->start();
}
