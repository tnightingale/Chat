#include <QByteArray>
#include <QObject>
#include <QMap>

class Socket;
class MainWindow;
class Room;
class Message;
class User;

class Client : public QObject {
  Q_OBJECT

private:
    /** The socket connected to the server. */
    Socket * serverSocket_;

    /** A pointer to the client's mainwindow. */
    MainWindow * mw_;

    /** Contains all of the rooms this user is a member of. */
    QMap<QString, Room *> * chatRooms_;

    /** This user's user object. */
    User * user_;


    /**
     * Display received messages in the GUI.
     *
     * @param msg The message to display.
     *
     * @author Tom Nightingale
     */
    void displayMessage(Message * msg);

    /**
     * Process a list of Users that are present in a rooom.
     * This gets called when you first join a room and when the server sends
     * any subsequent updates.
     * 
     * @param msg The message containing the user list.
     *
     * @author Tom Nightingale
     */
    void rxUserList(Message * msg);
  
public:
    Client(MainWindow * mw);
    virtual ~Client();

    /**
     * Connect to a server.
     *
     * @param port The port to connect to.
     * @param host The host name of the server to connect to.
     *
     * @author Tom Nightingale
     */
    bool connect(int port, QString * host);

    /**
     * Make a join room request to the server.
     *
     * @param roomName The name of the room to join.
     *
     * @author Tom Nightingale.
     */
    void joinRoom(QString roomName);

    /**
     * Sets user's nickname both remotely and locally.
     *
     * @param name The new name to set.
     *
     * @author Tom Nightingale
     */
    void setNick(QString name);

public slots:
    /**
     * Connects to a server and joins first room.
     *
     * @author Tom Nightingale
     */
    void slotConnect();

    /**
     * Prepares message for sending to server and display.
     *
     * @param message The message to process.
     * @param roomName The room the message belongs to.
     *
     * @author Tom Nightingale
     */
    void slotPrepMessage(QString * message, QString roomName);

    /**
     * Messages received on the socket get initially processed here.
     *
     * @param socketD Unused on client-side.
     * @param message The message received.
     *
     * @author Marcel Vangrootheest
     */
    void slotMessageRx(int, QByteArray * message);

    /**
     * Cleanup when user leaves room. Notifies server etc...
     *
     * @author Tom Nightingale
     */
    void slotLeaveRoom(QObject *);

    /**
     * When server notifies of client being added to a room, processing is done
     * here.
     *
     * @author Tom Nightingale
     */
    void addRoom();
};
