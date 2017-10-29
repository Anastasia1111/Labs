#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QMainWindow>

namespace Ui {
class DBWindow;
}

class DBWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBWindow(bool adminAccess, QWidget *parent = 0);
    ~DBWindow();

private slots:
    void on_actionExit_triggered();

private:
    Ui::DBWindow *ui;
    bool adminAccess;
};

#endif // DBWINDOW_H
