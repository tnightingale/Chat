#include "Socket.h"
#include "ConnectionManager.h"

Socket::Socket(QObject * parent) : QObject(parent) {
    if ((socket_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw "Socket::Socket(); Could not create socket.";
    }
}

Socket::Socket(int socketDescriptor) 
  : socket_(socketDescriptor), cThread_(NULL), cm_(NULL) {}

Socket::~Socket() {

    if (cm_ != NULL) {
        //delete cm_;
    }

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
        qDebug("Socket::listen(); Could not bind listening socket.");
    }

    // Listen for connections
    ::listen(socket_, 5);
    
    cm_ = new ConnectionManager(socket_);
    cThread_ = new QThread();

    // Wiring up connections.
    QObject::connect(cThread_, SIGNAL(started()),
            cm_, SLOT(start()));
    QObject::connect(cm_, SIGNAL(newConnection(int, char *)),
            parent(), SLOT(slotNewUser(int, char *)));
    QObject::connect(cm_, SIGNAL(closedConnection(int)),
            parent(), SLOT(slotUserDisconnected(int)));

    cm_->moveToThread(cThread_);

    cThread_->start();
}

bool Socket::connect(int port, const char * host) {
    hostent * hp;
    sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if ((hp = gethostbyname(host)) == NULL) {
        qDebug("Socket::connect(); Unknown server address: %s.", host);
        return false;
    }
    bcopy(hp->h_addr, (char *) &server.sin_addr, hp->h_length);

    // Connecting to the server
    if (::connect(socket_, (sockaddr *) &server, sizeof(server)) == -1) {
        qDebug("Socket::connect(); Can't connect to server: %s.", host);
        return false;
    }

    return true;
}


int Socket::read(QByteArray * buffer) {
    int n = 0;
    size_t numBytesToRead = BUFLEN;
    char * bp = buffer->data();

    while (numBytesToRead && (n = ::read(socket_, bp, numBytesToRead)) > 0) {
        // I don't think it is actually necessary to increment the 
        // bufferpointer, at least in MacOS... see read(2).
        bp += n;
        numBytesToRead -= n;

        if (numBytesToRead == 0 || *(bp - 1) == '\n') {
          *bp = '\0';
          break;
        }
    }

    return n;
}

int Socket::write(QByteArray * buffer) {
    const char * bp = buffer->constData();

    return ::write(socket_, bp, buffer->size());
}
