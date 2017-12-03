#include "server.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server* server = new Server();
    bool success = server->listen(QHostAddress::Any, 1337);
    if (!success)
    {
        qFatal("Couldn't listen on port 1337");
    }

    qDebug() << "Ready";

    return a.exec();
}
