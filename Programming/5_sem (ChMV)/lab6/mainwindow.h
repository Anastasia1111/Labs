#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crypter.h"
#include "dialog.h"
#include "database.h"
#include "dbwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_remember_clicked();

    void on_pushButtonNext_clicked();

private:
    Ui::MainWindow *ui;
    DataBase *db;
    QMap< QPair<QString, QString>, QPair<QString, QString> > *map;

};

#endif // MAINWINDOW_H
