#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSettings>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextCodec>

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
    void on_actionBack_triggered();

    void on_actionForward_triggered();

    void on_actionReload_triggered();

    void on_actionStop_triggered();

    void on_webView_loadProgress(int progress);

    void smartLoad(QString value);

    void on_urlPath_returnPressed();

    void on_webView_loadFinished(bool arg1);

    void replyFinished();

    void on_pushButtonPOST_clicked();

    void on_pushButtonGET_clicked();

    void on_webView_linkClicked(const QUrl &arg1);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // MAINWINDOW_H
