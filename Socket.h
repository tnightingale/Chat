#include <QDebug>
#include <QObject>
#include <QThread>
#include <netinet/in.h>
#include <sys/socket.h>

namespace Nightingale {

class ConnectionManager;

class Socket : public QObject {
  Q_OBJECT

private:
    int socket_;
    QThread * cThread_;
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

    void listen(int port);

};

}
