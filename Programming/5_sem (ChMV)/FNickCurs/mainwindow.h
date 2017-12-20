#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QModelIndex>
#include <QMessageBox>
#include <QMap>

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

signals:
    void usedBougetteUpdated(int value);

private slots:
    void on_buttonOrganize_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_buttonBack_clicked();

    void on_buttonDelete_clicked();

    void nameChange(QString arg);

    void updateUsedBougette();

    void on_buttonCancel_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
    DataBase *db;
    QSqlRelationalTableModel *wedMod;
    QSqlRelationalTableModel *evMod;
    bool editMode;
    QModelIndex curWedding;
    QMap<int, int> evIndex;
};

#endif // MAINWINDOW_H
