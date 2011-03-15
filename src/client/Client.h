#include <QByteArray.h>
#include <QObject.h>

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

    void connect(int port, QString * host);

public slots:
    void slotConnect();
    void slotPrepMessage(QString * message);
};
