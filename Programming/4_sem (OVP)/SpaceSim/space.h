#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class Space;
}

class Space : public QMainWindow
{
    Q_OBJECT

public:
    explicit Space(QWidget *parent = 0);
    ~Space();

private slots:
    void on_actionFile_triggered();

protected:
    virtual void timerEvent(QTimerEvent *e);

private:
    Ui::Space *ui;
    QColor starColor;
    QColor spaceColor;
};

#endif // MAINWINDOW_H
