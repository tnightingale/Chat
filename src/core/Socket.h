#include <QDebug>
#include <QObject>
#include <QThread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUFLEN 255

class ConnectionManager;

class Socket : public QObject {
  Q_OBJECT

private:
    /**
     * The socket descriptor.
     */
    int socket_;

    /**
     * The connection manager thread.
     */
    QThread * cThread_;

    /**
     * The connection manager.
     */
    ConnectionManager * cm_;

public:
    Socket(QObject * parent = 0);
    Socket(int socketDescriptor);
    virtual ~Socket();

    /**
     * Gets the socket descriptor.
     *
     * @author Tom Nightingale
     */
    int getSocketD() { return socket_; }

    /**
     * Gets the connection manager.
     *
     * @author Tom Nightingale
     */
    const ConnectionManager * getCM() { return cm_; }

    /**
     * Binds socket to specific port and begins listening. Listening is done in
     * cThread_ and mangaged by the ConnectionManager.
     */
    void listen(int port);

    /**
     * Connects to host on specified port.
     */
    void connect(int port, char * host);

    /**
     * Reads data from socket. 
     *
     * @param buffer The buffer to read into.
     *
     * @author Tom Nightingale
     */
    int read(QByteArray * buffer);

    /**
     * Writes data to the socket. 
     *
     * @param buffer The buffer containing data to write.
     *
     * @author Tom Nightingale
     */
    int write(QByteArray * buffer);
};

