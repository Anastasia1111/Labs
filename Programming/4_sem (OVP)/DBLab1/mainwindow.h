#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QModelIndex>
#include <QFileDialog>

#include "database.h"

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

    void on_pushButton_Sort_clicked();

    void on_lineEdit_CharSearch_textChanged(const QString &arg1);

    void on_lineEdit_WordSearch_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    //QSqlDatabase db;
    DataBase *db;
    QSqlRelationalTableModel *mod_Fc;
    QSqlRelationalTableModel *mod_Gr;
    QSqlRelationalTableModel *mod_St;
    QString filename;
    Qt::SortOrder lastOrder;
};

#endif // MAINWINDOW_H
