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

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "StudentsDataBase"

#define TABLE1                  "Faculty"               // Название таблицы 1
#define TABLE1_FAC              "Faculty"               // Вторая колонка таблицы 1
#define TABLE1_YEAR             "Year"                  // Третья колонка таблицы 1
#define TABLE1_GRNUM            "Number of groups"      // Четвертая колонка таблицы 1
#define TABLE2                  "Groups"                 // Название таблицы 2
#define TABLE2_NAME             "Group_name"            // Вторая колонка таблицы 2
#define TABLE2_LNAME            "Name of elder"         // Третья колонка таблицы 2
#define TABLE2_NUM              "Number of students"    // Четвертая колонка таблицы 2
#define TABLE2_FAC              "Faculty ID"            // Пятая колонка таблицы 2
#define TABLE3                  "Students"              // Название таблицы 3
#define TABLE3_FN               "Full name"             // Вторая колонка таблицы 3
#define TABLE3_ADDS             "Address"               // Третья колонка таблицы 3
#define TABLE3_PNUM             "Phone number"          // Четвертая колонка таблицы 3
#define TABLE3_IDGR             "ID_GR"                 // Пятая колонка таблицы 3

// Первая колонка содержит Autoincrement ID

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase(const QString &name);

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase(const QString &name);         // Открытие базы данных
    bool restoreDataBase(const QString &name);      // Восстановление базы данных
    void closeDataBase();                           // Закрытие базы данных
    bool createTables();                            // Создание таблиц в базе данных

public slots:
    bool injectSQL(const QString &code);            // Внедрение SQL кода
};

#endif // DATABASE_H