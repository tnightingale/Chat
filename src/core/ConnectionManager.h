#include <QObject>
#include <QMap>
#include <netinet/in.h>
#include <arpa/inet.h>

class Socket;
class Message;

class ConnectionManager : public QObject {
  Q_OBJECT

private:
    /** The the socket which owns this connectionmanager. */
    Socket * parentSocket_;

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
    ConnectionManager(Socket * parentSocket);

    /**
     * Destructor.
     *
     * @author Tom Nightingale.
     */
    virtual ~ConnectionManager();

signals:
    /**
     * Signal a new connection.
     *
     * @param newSD The socket descriptor.
     * @param address The address of the client.
     *
     * @author Tom Nightingale
     */
    void newConnection(int newSD, char * address);

    /**
     * Signal a closed connection.
     *
     * @param socketD The socket whose connection was closed.
     *
     * @author Tom Nightingale
     */
    void closedConnection(int socketD);

    /**
     * Signal that a message has been received.
     *
     * @param socketD The socket descriptor on which the message was received.
     * @param buffer A pointer to a buffer containing the received message.
     *
     * @author Tom Nightingale
     */
    void messageReceived(int socketD, QByteArray * buffer);

public slots:

    /**
     * Listen for connections. This is for server side usage. Will call accept()
     * and open new client sockets.
     *
     * @author Tom Nightingale
     */
    void listenForConnections();

    /**
     * Listen to socket for messages. This is for client side usage.
     *
     * @author Tom Nightingale
     */
    void listenForMessages();

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

