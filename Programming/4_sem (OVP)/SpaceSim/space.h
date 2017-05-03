#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QLabel>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QColorDialog>

#include "flyobject.h"
#include "asteroidbelt.h"
#include "winchange.h"

#define CRASH_DIST 0.25
#define KEY_MOVE_PX 20

namespace Ui {
class Space;
}

class Space : public QMainWindow
{
    Q_OBJECT

    enum CollisionSolveType{
        MERGE = 1,
        DESTR = 2,
        STOP = 3
    };

public:
    explicit Space(QWidget *parent = 0);
    ~Space();

    void spaceInit();
    FlyObject *merge(FlyObject *obj1, FlyObject *obj2);

private slots:
    void on_actionFile_triggered();

    void on_actionNew_triggered();

    bool on_actionSave_triggered();

    void on_actionSP_triggered();

    void on_actionSize_triggered();

    void on_actionKey_Up_triggered();

    void on_actionKey_Down_triggered();

    void on_actionKey_Left_triggered();

    void on_actionKey_Right_triggered();

    void on_actionDestr_triggered();

    void on_actionStop_triggered();

    void on_actionMerge_triggered();

    void on_actionSpace_color_triggered();

    void on_actionStars_color_triggered();

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
    qint32 topLeftX, topLeftY;

    QList<FlyObject *> system;

    QString fileName;
    bool saved;
    bool paused;

    QLabel *runningStr;
};

#endif // MAINWINDOW_H
