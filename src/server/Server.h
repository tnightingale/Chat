#include <QObject>
#include <QMap>

class Socket;
class User;
class Room;
class Message;

class Server : public QObject {
  Q_OBJECT

private:
    /** The server's listening port. */
    int port_;

    /** The server's listening socket. */
    Socket * listenSock_;

    /** Collection of connected users. */
    QMap<int, User *> * users_;

    /** Collection of rooms. */
    QMap<QString, Room *> * rooms_;

public:
    Server();
    virtual ~Server();

    /**
     * Start listening for incoming connections.
     *
     * @param port The port number to listen to.
     * 
     * @author Tom Nightingale
     */
    void listen(int port = 7000);

    void forwardMessage(User * sender, Message * msg);
    void userJoinRoom(User * sender, Message * msg);
    QByteArray prepareUserList(QSet<User *> users);

signals:
    void bcstMsg(QByteArray * message, QSet<int> * users);

public slots:
    void slotNewUser(int socketDescriptor, char * address);
    void slotUserDisconnected(int socketDiscriptor);
    void slotMessageRx(int socketDiscriptor, QByteArray * buffer);
};
