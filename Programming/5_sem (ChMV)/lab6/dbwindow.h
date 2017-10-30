#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include "database.h"
#include "crypter.h"

namespace Ui {
class DBWindow;
}

class DBWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBWindow(QString login, QSqlDatabase db, QWidget *parent = 0);
    ~DBWindow();

private slots:
    void on_actionExit_triggered();

    void on_lineEdit_CharSearch_textChanged(const QString &arg1);

    void on_lineEdit_WordSearch_textChanged(const QString &arg1);

    void on_actionNewUser_triggered();

    void on_actionChangePassword_triggered();

private:
    Ui::DBWindow *ui;
    QString login;
    QSqlTableModel* mod;
    QSqlDatabase db;
};

#endif // DBWINDOW_H
