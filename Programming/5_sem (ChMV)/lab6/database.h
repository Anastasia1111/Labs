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
#define DATABASE_HOSTNAME   "PoolDataBase"

#define TABLE1          "Clients"                   // Название таблицы 1
#define TABLE1_FN       "Fullname"                  // Вторая колонка таблицы 1
#define TABLE1_GND      "Gender"                    // Третья колонка таблицы 1
#define TABLE1_PNUM     "Phone_number"              // Четвертая колонка таблицы 1
#define TABLE1_REGDT    "Registration_date"         // Пятая колонка таблицы 1
#define TABLE1_SUBDR    "Subscripton_duration"      // Шестая колонка таблицы 1
#define TABLE1_PSTDT    "Previous_subscriptions"    // Седьмая колонка таблицы 1
#define TABLE1_PHOTO    "Doctor_note_photo"         // Восьмая колонка таблицы 1
#define TABLE1_NOTDR    "Doctor_note_duration"      // Девятая колонка таблицы 1
#define TABLE2          "Users"                     // Название таблицы 2
#define TABLE2_LOG      "Login"                     // Вторая колонка таблицы 2
#define TABLE2_PAS      "Password"                  // Третья колонка таблицы 2
#define TABLE2_QST      "Question"                  // Четвертая колонка таблицы 2
#define TABLE2_ANS      "Answer"                    // Пятая колонка таблицы 2

// Первая колонка содержит Autoincrement ID

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     */
    void connectToDataBase(const QString &name);

    QSqlDatabase getDB();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    // Внутренние методы для работы с базой данных
    bool openDataBase(const QString &name);     // Открытие базы данных
    bool restoreDataBase(const QString &name);  // Восстановление базы данных
    void closeDataBase();                       // Закрытие базы данных
    bool createTables();                        // Создание таблиц в базе данных

};

#endif // DATABASE_H
