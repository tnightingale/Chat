#include <QDebug>
#include <QObject>
#include <QThread>
#include <netinet/in.h>
#include <sys/socket.h>

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
    Socket();
    virtual ~Socket();

    /**
     * Gets the socket descriptor.
     *
     * @author Tom Nightingale.
     */
    int getSocketD() { return socket_; }

    /**
     * Binds socket to specific port and begins listening. Listening is done in
     * cThread_ and mangaged by the ConnectionManager.
     */
    void listen(int port);
};

