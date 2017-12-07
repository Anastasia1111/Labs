#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QListWidget>

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
    void on_loginButton_clicked();
    void on_sayButton_clicked();
    void on_actionDisconnect_triggered();
    void on_sayLineEdit_returnPressed();
    void on_userListWidget_itemClicked(QListWidgetItem *item);
    void onReady();
    void onConnect();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QListWidgetItem *partner;
};

#endif // MAINWINDOW_H
