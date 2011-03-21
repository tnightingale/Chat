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
    Socket * serverSocket_;
    MainWindow * mw_;
    QMap<QString, Room *> * chatRooms_;
    User * user_;

    void displayMessage(Message * msg);
    void rxUserList(Message * msg);
  
public:
    Client(MainWindow * mw);
    virtual ~Client();

    bool connect(int port, QString * host);

    void joinRoom(QString roomName);
    void setNick(QString name);

signals:
    void newRoom();

public slots:
    void slotConnect();
    void slotPrepMessage(QString * message, QString roomName);
    void slotMessageRx(int, QByteArray * message);
    void slotLeaveRoom(QObject *);
    void addRoom();
};
