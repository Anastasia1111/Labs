+
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileSystemModel* baseModel;
    QFileSystemModel* fileModel;
    QLabel* labelPath;
    QLabel* labelNameSize;
    QLabel* labelTime;
    bool timeTracking;

public slots:
    void setIndexChanged(int num);

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_filterComboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

protected:
    virtual void timerEvent(QTimerEvent *e);
};

#endif // MAINWINDOW_H
