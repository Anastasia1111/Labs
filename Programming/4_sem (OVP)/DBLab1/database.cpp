#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
    this->closeDataBase();
}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase(const QString &name)
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile(name).exists()){
        qDebug() << "Try to restore DB";
        this->restoreDataBase(name);
    } else {
        qDebug() << "Try to open DB";
        this->openDataBase(name);
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase(const QString &name)
{
    // Если база данных открылась ...
    if(this->openDataBase(name)){
        // Производим восстановление базы данных
        qDebug() << "Can restore DB";
        return (this->createTables()) ? true : false;
    } else {
        qDebug() << "Can't restore DB";
        qDebug() << db.lastError().text();
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase(const QString &name)
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(name);
    if(db.open()){
        qDebug() << "Can open DB " << name;
        return true;
    } else {
        qDebug() << "Can't open DB " << name;
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблиц в базе данных
 * */
bool DataBase::createTables()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE1 " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE1_FAC      " VARCHAR(255)  NOT NULL,"
                    TABLE1_YEAR     " VARCHAR(255)  NOT NULL,"
                    TABLE1_GRNUM    " VARCHAR(255)  NOT NULL"
                " )"
            ) ||
        !query.exec( "CREATE TABLE " TABLE2 " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE2_NAME     " VARCHAR(255)  NOT NULL,"
                    TABLE2_LNAME    " VARCHAR(255)  NOT NULL,"
                    TABLE2_NUM      " VARCHAR(255)  NOT NULL,"
                    TABLE2_FAC      " INTEGER       NOT NULL"
                " )"
            ) ||
        !query.exec( "CREATE TABLE " TABLE3 " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE3_FN       " VARCHAR(255)  NOT NULL,"
                    TABLE3_ADDS     " VARCHAR(255)  NOT NULL,"
                    TABLE3_PNUM     " VARCHAR(255)  NOT NULL,"
                    TABLE3_IDGR     " INTEGER       NOT NULL"
                " )"
            )
    ){
        qDebug() << "DataBase: error of create tables";
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки SQL кода в базу данных
 * */
bool DataBase::injectSQL(const QString &code)
{
    QSqlQuery query;

    if(!query.exec(code)){
        qDebug() << "error injecting SQL code";
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}