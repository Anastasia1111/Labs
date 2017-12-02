#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QTextCodec>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QList>
#include <QPixmap>

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
    void on_loadPushButton_clicked();
    void on_urlLineEdit_returnPressed();
    void on_updatePushButton_clicked();
    void on_forwardPushButton_clicked();
    void on_backPushButton_clicked();
    void on_webView_urlChanged(const QUrl &arg1);
    void on_comboBox_activated(int index);
    void on_searchPushButton_clicked();
    void on_searchLineEdit_returnPressed();
    void weatherReplyFinished();
    void updateWeather();
    void loginReplyFinished();
    void on_loginPushButton_clicked();
    void on_downloadPushButton_clicked();
    void downloadReplyFinished();
    void replyFinished_POST();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QNetworkAccessManager *manager;
};

#endif // MAINWINDOW_H
