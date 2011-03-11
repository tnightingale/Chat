#include <QObject>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace Nightingale {

class ConnectionManager : public QObject {
private:
    int listen_sd_;
    int clients_[FD_SETSIZE];
    fd_set allset_;
    int maxfd_;
    int maxi_;

public:
    ConnectionManager(int socketD);

public slots:
    void start();
};

}
