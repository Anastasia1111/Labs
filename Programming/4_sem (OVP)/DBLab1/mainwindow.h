#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QModelIndex>
#include <QFileDialog>

#include "database.h"
#include "addrec.h"

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

    void setDefaultValues();

    void setupTables();

    void on_pushButton_Sort_clicked();

    void on_lineEdit_CharSearch_textChanged(const QString &arg1);

    void on_lineEdit_WordSearch_textChanged(const QString &arg1);

    void on_pushButton_AddRecord_clicked();

    void on_actionAbout_LW_triggered();

    void on_actionInsert_SQL_code_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_pushButton_DeleteRecord_clicked();

    void on_actionExport_triggered();

private:
    Ui::MainWindow *ui;
    DataBase *db;
    QVector<QSqlRelationalTableModel*> mod;
    QVector<QTableView*> view;
    Qt::SortOrder lastOrder;
    AddRec* dialogWin;
};

#endif // MAINWINDOW_H
