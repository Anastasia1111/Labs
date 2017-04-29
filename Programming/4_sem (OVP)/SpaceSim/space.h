#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "flyobject.h"
#include "asteroidbelt.h"

namespace Ui {
class Space;
}

class Space : public QMainWindow
{
    Q_OBJECT

    enum CollisionSolveType{
        JOIN = 1,
        DESTR = 2,
        STOP = 3
    };

public:
    explicit Space(QWidget *parent = 0);
    ~Space();

    void spaceInit();
    FlyObject *join(FlyObject *obj1, FlyObject *obj2);

private slots:
    void on_actionFile_triggered();

    bool on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSP_triggered();

protected:
    virtual void timerEvent(QTimerEvent *e);
    virtual void closeEvent(QCloseEvent *e);

private:
    Ui::Space *ui;
    QColor starColor;
    QColor spaceColor;
    qint32 stars;
    qint32 csType;
};

#endif // MAINWINDOW_H
