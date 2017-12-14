#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME   "Organizator"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    void connectToDataBase(const QString &name);

    QSqlDatabase getDB();

private:
    QSqlDatabase db;

private:
    bool openDataBase(const QString &name);
    void closeDataBase();
};

#endif // DATABASE_H
