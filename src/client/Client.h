#include <QByteArray>
#include <QObject>
#include <QMap>

class Socket;
class MainWindow;
class Room;
class Message;

class Client : public QObject {
  Q_OBJECT

private:
    Socket * serverSocket_;
    MainWindow * mw_;
    QMap<QString, Room *> * chatRooms_;
  
public:
    Client(MainWindow * mw);
    virtual ~Client();

    bool connect(int port, QString * host);

    //void initRoom(QString name);

    void sendUserList(Room room);

    void joinRoom(QString roomName);

signals:
    void newRoom();

public slots:
    void slotConnect();
    void slotPrepMessage(QString * message, QString roomName);
    void slotDisplayMessage(int, QByteArray * message);
    //void addRoom();
    void updateUsers(QByteArray * buffer);
};
