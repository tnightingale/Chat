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


    void broadcastUserList(Room * room);

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

    /**
     * Send messages on to everyone in room exept for the sender.
     * Sender can be NULL.
     *
     * @param sender The sender of the forwarded message.
     * @param msg The message to forward.
     * 
     * @author Tom Nightingale
     */
    void forwardMessage(User * sender, Message * msg);

    /**
     * Add user to a room. If room doesn't exist, create it.
     *
     * @param sender The client requesting the room add.
     * @param msg The requesting message.
     * 
     * @author Tom Nightingale
     */
    void userJoinRoom(User * sender, Message * msg);

    /**
     * Notification of a user leaving a room.
     *
     * @param sender The user leaving the room.
     * @param msg The message.
     * 
     * @author Tom Nightingale
     */
    void userLeaveRoom(User * sender, Message * msg);

    /**
     * Request from client to change user name.
     *
     * @param sender The client requesting the name change.
     * @param msg The requesting message.
     * 
     * @author Tom Nightingale
     */
    void userSetNick(User * sender, Message * msg);

    /**
     * Prepare user list for broadcast.
     *
     * @param users A set of users to send to.
     * 
     * @author Tom Nightingale
     */
    QByteArray prepareUserList(QSet<User *> * users);

signals:
    void bcstMsg(QByteArray * message, QSet<int> * users);

public slots:
    void slotNewUser(int socketDescriptor, char * address);
    void slotUserDisconnected(int socketDiscriptor);
    void slotMessageRx(int socketDiscriptor, QByteArray * buffer);
};
