#include <QObject>
#include <netinet/in.h>
#include <arpa/inet.h>

class ConnectionManager : public QObject {
  Q_OBJECT

private:
    /** The listening socket descriptor. */
    int listenSocketD_;

    /** List of client socket descriptors. */
    int clients_[FD_SETSIZE];

    /** Descriptor set for select(). */
    fd_set allset_;

    /** Highest descriptor. */
    int maxfd_;

    /** The most recent position a client socket descriptor was added to 
     *  clients_. */
    int maxi_;

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
    void newConnection(int newSD,  char * address);

public slots:
    void start();

private:
    /**
     * Accept connections and open client sockets. For internal use only.
     *
     * @author Tom Nightingale
     */
    void accept();

};

