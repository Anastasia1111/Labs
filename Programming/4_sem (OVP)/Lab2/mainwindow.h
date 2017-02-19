#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class MainWindow;
}
class QLabel;
class QSlider;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel* labelX;
    QLabel* labelY;
    QSlider* sliderPen;

private slots:
    //void slotOpen();
    //void slotSave();
    void slotAboutProgram();

protected:
    virtual void timerEvent(QTimerEvent* e);
};

#endif // MAINWINDOW_H
