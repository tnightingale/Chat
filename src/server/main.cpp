#include <QCoreApplication>
#include "./Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server* server = new Server();
    server->listen(7000);

    return a.exec();
}
