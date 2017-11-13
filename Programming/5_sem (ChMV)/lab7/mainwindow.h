#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTemporaryFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include "domparser.h"
#include "saxparser.h"

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

    void on_open_clicked();

    void on_textEdit_textChanged();

    void on_clear_clicked();

    void on_exit_clicked();

    void on_update_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *time;
    QString fileName;
    QString tmpFileName;
};

#endif // MAINWINDOW_H
