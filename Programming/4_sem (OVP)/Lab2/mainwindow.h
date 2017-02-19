#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

protected:
    virtual void mouseMoveEvent(QMouseEvent* e);
};

#endif // MAINWINDOW_H
