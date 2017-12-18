#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QModelIndex>
#include <QMessageBox>

#include "database.h"
#include "dialog.h"
#include "page.h"

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
    void on_buttonOrganize_clicked();

    void on_actionOrganize_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_buttonBack_clicked();

    void on_buttonDelete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void nameChange(QString arg);

    void on_buttonCancel_clicked();

private:
    Ui::MainWindow *ui;
    DataBase *db;
    QSqlRelationalTableModel *wedMod;
    bool deleteMode;
    bool editMode;
};

#endif // MAINWINDOW_H
