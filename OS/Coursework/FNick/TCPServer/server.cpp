#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
}

void Server::incomingConnection(int socketfd)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    qDebug() << "New client from:" << client->peerAddress().toString();

    connect(client, SIGNAL(readyRead()), this, SLOT(onReady()));
    connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
}

void Server::onReady()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << "Read line:" << line;

        QRegExp meRegex("^/me:(.*)$");
        QRegExp privRegex("^/to:(.*)$");

        if(meRegex.indexIn(line) != -1) // Сообщение на присоединение
        {
            QString user = meRegex.cap(1);
            users[client] = user;
            foreach(QTcpSocket *client, clients)
                client->write(QString("Server:" + user + " has joined.\n").toUtf8());
            sendUserList();
        }
        else if(privRegex.indexIn(line) != -1) // Приватное сообщение
        {
            QStringList usrNmsg = privRegex.cap(1).split(",");
            QString reciver = usrNmsg.at(0);
            QString msg = usrNmsg.at(1);
            QString usr = users[client];
            foreach(QTcpSocket *otherClient, clients)
                if (users[otherClient] == reciver || users[otherClient] == usr)
                {
                    otherClient->write(QString("<i>" + usr + "</i>:" + msg + "\n").toUtf8());
                    break;
                }
        }
        else if(users.contains(client)) // Обычное сообщение
        {
            QString msg = line;
            QString usr = users[client];
            qDebug() << "User:" << usr;
            qDebug() << "Message:" << msg;

            foreach(QTcpSocket *otherClient, clients)
                otherClient->write(QString(usr + ":" + msg + "\n").toUtf8()); // На самом деле отправляется всем клиентам, а не только другим. Я просто не придумал другого названия переменной(
        }
        else
        {
            qWarning() << "Got bad message from client:" << client->peerAddress().toString() << line;
        }
    }
}

void Server::onDisconnect()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();

    clients.remove(client);

    QString user = users[client];
    users.remove(client);

    sendUserList();
    foreach(QTcpSocket *client, clients)
        client->write(QString("Server:" + user + " has left.\n").toUtf8());
}

void Server::sendUserList()
{
    QStringList userList;
    foreach(QString user, users.values())
        userList << user;

    foreach(QTcpSocket *client, clients)
        client->write(QString("/users:" + userList.join(",") + "\n").toUtf8());
}
