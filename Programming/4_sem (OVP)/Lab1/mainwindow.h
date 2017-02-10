#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class MainWindow;
}
class AddRec;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotOpen();
    void slotSave();
    void slotAboutProgram();

    void on_pushButton_Start_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_Search_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::MainWindow *ui;
    AddRec* dialogWin;
};

#endif // MAINWINDOW_H
