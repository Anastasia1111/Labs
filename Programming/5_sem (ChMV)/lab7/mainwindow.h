#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTemporaryFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QTimer>

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
    void on_save_clicked();

    void on_save_as_clicked();

    void temporaryFileSave();

private:
    Ui::MainWindow *ui;
    QFile *tmpFile;
    QTimer *time;
    QString fileName;
};

#endif // MAINWINDOW_H
