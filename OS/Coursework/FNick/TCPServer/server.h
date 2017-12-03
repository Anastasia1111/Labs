#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include <QRegExp>
#include <QDebug>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

private slots:
    void onReady();
    void onDisconnect();

protected:
    void incomingConnection(int socketfd);

private:
    void sendUserList();

    QSet<QTcpSocket*> clients;
    QMap<QTcpSocket*, QString> users;
};

#endif // SERVER_H
