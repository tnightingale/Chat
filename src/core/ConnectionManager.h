#include <QObject>
#include <QMap>
#include <netinet/in.h>
#include <arpa/inet.h>

class Socket;
class ConnectionManager : public QObject {
  Q_OBJECT

private:
    /** The listening socket descriptor. */
    int listenSocketD_;

    /** List of client socket descriptors. */
    QMap<int, Socket *> * clients_;

    /** Descriptor set for select(). */
    fd_set allset_;

    /** Highest descriptor. */
    int maxfd_;

public:
    /**
     * Constructor.
     * Takes a socket descriptor to listen for connections on.
     *
     * @author Tom Nightingale
     */
    ConnectionManager(int listenSocketD);

    /**
     * Destructor.
     *
     * @author Tom Nightingale.
     */
    virtual ~ConnectionManager();

signals:
    void newConnection(int newSD, char * address);
    void closedConnection(int socketD);
    void userSetNick(int newSD, char * nick);

public slots:
    void start();

private:
    /**
     * Accept connections and open client sockets. For internal use only.
     *
     * @author Tom Nightingale
     */
    void accept();

    /**
     * Performs processing on a socket, this involves reading from the socket,
     * forwarding messages on to their correct destination, detecting
     * remote disconnections and closing sockets accordingly.
     *
     * @param a socket to be processed.
     *
     * @author Tom Nightingale.
     */
    void process(Socket * socket); 

};

