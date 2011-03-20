#include <QByteArray>
#include <QObject>

class Socket;
class MainWindow;

class Client : public QObject {
  Q_OBJECT

private:
    Socket * serverSocket_;
    MainWindow * mw_;
  
public:
    Client(MainWindow * mw);
    virtual ~Client();

    bool connect(int port, QString * host);

signals:
    void newRoom();

public slots:
    void slotConnect();
    void slotPrepMessage(QString * message);
    void slotDisplayMessage(QByteArray * message);
    void addRoom();
};
