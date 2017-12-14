#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
    this->closeDataBase();
}

void DataBase::connectToDataBase(const QString &name)
{
    if(!QFile(name).exists()){
        qCritical() << "DataBase doesn't exist!";
    } else {
        qDebug() << "Try to open DB";
        this->openDataBase(name);
    }
}

QSqlDatabase DataBase::getDB()
{
    return db;
}

bool DataBase::openDataBase(const QString &name)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(name);
    if(db.open()){
        qDebug() << "Can open DB: " << name;
        return true;
    } else {
        qDebug() << "Can't open DB: " << name;
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}
