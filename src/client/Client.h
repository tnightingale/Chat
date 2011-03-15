#include <QObject.h>

class Socket;

class Client : public QObject {
  Q_OBJECT

private:
    Socket * serverSocket_;
  
public:
    Client();
    virtual ~Client();

};
