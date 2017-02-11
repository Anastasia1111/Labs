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
class QListWidget;

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

    void on_pushButton_del_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_sort1_clicked();

    void on_pushButton_sort2_clicked();

private:
    Ui::MainWindow *ui;
    AddRec* dialogWin;

    void sortItemsByLength(Qt::SortOrder order, QListWidget* list);
};

#endif // MAINWINDOW_H
