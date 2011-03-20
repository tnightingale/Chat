#include <QByteArray>
#include <QObject>

class Socket;
class MainWindow;
class Room;

class Client : public QObject {
  Q_OBJECT

private:
    Socket * serverSocket_;
    MainWindow * mw_;
    QVector<Room*> * chatRooms_;
  
public:
    Client(MainWindow * mw);
    virtual ~Client();

    bool connect(int port, QString * host);

    void initRoom(QString name);

signals:
    void newRoom();

public slots:
    void slotConnect();
    void slotPrepMessage(QString * message, QString roomName);
    void slotDisplayMessage(QByteArray * message);
    void addRoom();
};
