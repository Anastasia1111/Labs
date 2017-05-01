#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "flyobject.h"
#include "asteroidbelt.h"

#define CRASH_DIST 0.5
#define OUT_DIST 10000
#define STEPS 5
#define KEY_MOVE_PX 20

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

    void on_actionNew_triggered();

    bool on_actionSave_triggered();

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

    qint32 width;
    qint32 height;

    QList<AsteroidBelt *> belts;
    QList<FlyObject *> objects;

    QString fileName;
    bool saved;
};

#endif // MAINWINDOW_H
