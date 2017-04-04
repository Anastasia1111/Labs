#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

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

    void on_pushButton_clicked();

    void on_lineEdit_CharSearch_textChanged(const QString &arg1);

    void on_lineEdit_WordSearch_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QString filename;
    Qt::SortOrder lastOrder;
};

#endif // MAINWINDOW_H
