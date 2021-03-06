#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

#include "paintscene.h"
#include "colordialog.h"

namespace Ui {
class MainWindow;
}
class QLabel;
class QSlider;
class QGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel* labelXY;
    QSlider* sliderPen;
    PaintScene *scene;  // Объявляем кастомную графическую сцену


private slots:
    int on_actionNew_triggered();

    void on_actionAbout_triggered();

    void on_actionColor_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSolid_triggered();

    void on_actionDot_triggered();

    void on_actionDashDotDot_triggered();

protected:
    virtual void timerEvent(QTimerEvent *e);
    virtual void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H