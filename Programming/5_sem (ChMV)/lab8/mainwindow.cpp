#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->webView->load(QUrl("http://google.ru"));
    updateWeather();
    timer = new QTimer();
    timer->setInterval(3000);
    timer->start();
    manager = new QNetworkAccessManager(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWeather()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    if (!ui->urlLineEdit->text().isEmpty())
    {
        QString validLink = ui->urlLineEdit->text();
        if (validLink.toLower().startsWith("http:\\") || validLink.toLower().startsWith("ftp:\\"))
        {
            validLink = validLink.replace(":\\","://");
        }
        if (!validLink.toLower().startsWith("http") && !validLink.toLower().startsWith("ftp"))
        {
            validLink = "http://" + validLink;
        }
        ui->webView->load(validLink);
    }
}

void MainWindow::on_urlLineEdit_returnPressed()
{
    on_loadPushButton_clicked();
}

void MainWindow::on_updatePushButton_clicked()
{
    ui->webView->reload();
}

void MainWindow::on_forwardPushButton_clicked()
{
    ui->webView->forward();
}

void MainWindow::on_backPushButton_clicked()
{
    ui->webView->back();
}


void MainWindow::on_webView_urlChanged(const QUrl &arg1)
{
    ui->urlLineEdit->setText(arg1.toString());
}

void MainWindow::on_comboBox_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->webView->load(QUrl("http://google.ru"));
        break;
    case 1:
        ui->webView->load(QUrl("http://cyber.sibsutis.ru:82"));
        break;
    case 2:
        ui->webView->load(QUrl("http://cn.ru"));
        break;
    }
}

void MainWindow::updateWeather()
{
    QString weatherUrl = "http://api.openweathermap.org/data/2.5/weather?id=1496747&appid=1de079ea6e6386f5366c91d12ba204c3";
    QNetworkRequest request(weatherUrl);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(weatherReplyFinished()));
}

void MainWindow::weatherReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray bytes = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(bytes);
    QJsonObject object = document.object();
    double temperature = object["main"].toObject()["temp"].toDouble() - 273.15;
    QString str = QString::number(temperature);
    ui->weatherLabel->setText("Текущая температура:" + str);
    reply->deleteLater();
    timer->start();
}

void MainWindow::on_searchPushButton_clicked()
{
    if (!ui->searchLineEdit->text().isEmpty())
    {
        QUrl url;
        switch(ui->searchComboBox->currentIndex())
        {
        case 0:
            url.setUrl("http://google.ru/search?q=" + ui->searchLineEdit->text());
            break;
        case 1:
            url.setUrl("http://search.yahoo.com/search?p=" + ui->searchLineEdit->text());
            break;
        case 2:
            url.setUrl("http://www.bing.com/search?q=" + ui->searchLineEdit->text());
            break;
        case 3:
            url.setUrl("http://nova.rambler.ru/search?query=" + ui->searchLineEdit->text());
            break;
        case 4:
            url.setUrl("http://yandex.ru/search/?lr=65&text=" + ui->searchLineEdit->text());
            break;
        case 5:
            url.setUrl("http://go.mail.ru/search?q=" + ui->searchLineEdit->text());
            break;
        }
        ui->webView->load(url);
    }
}

void MainWindow::on_searchLineEdit_returnPressed()
{
    on_searchPushButton_clicked();
}

void MainWindow::on_loginPushButton_clicked()
{
    QString user = "wiwopamuko@p33.org";
    QString pass = "71yH@V";
    QUrl urlDoLogin("http://www.cyberforum.ru/login.php");
    QByteArray postData;
    postData += "vb_login_username=" + QUrl::toPercentEncoding(user.toUtf8());
    postData += "&cookieuser=1";
    postData += "&vb_login_password=" + QUrl::toPercentEncoding(pass.toUtf8());
    postData += "&s=&securitytoken=guest";
    postData += "&do=login";
    postData += "&vb_login_md5password=";
    postData += "&vb_login_md5password_utf=";
    QNetworkRequest request(urlDoLogin);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Accept-Encoding", "identity");
    QNetworkReply *reply = manager->post(request, postData);
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished_POST()));
}

void MainWindow::replyFinished_POST()
{
    QUrl urlUser("http://www.cyberforum.ru/usercp.php");
    QNetworkRequest request(urlUser);
    request.setRawHeader("Accept-Encoding", "identity");
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(loginReplyFinished()));
}

void MainWindow::loginReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QByteArray content = reply->readAll();
    QTextCodec *codec = QTextCodec::codecForName("cp1251");
    ui->webView->setHtml(codec->toUnicode(content.data()));
    ui->urlLineEdit->setText(reply->url().toString());
    reply->deleteLater();
}

void MainWindow::on_downloadPushButton_clicked()
{
    QUrl url("http://cyber.sibsutis.ru/theme/formal_white/logo_small.jpg");
    QNetworkRequest request(url);
    request.setRawHeader("Accept-Encoding", "identity");
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(downloadReplyFinished()));
}

void MainWindow::downloadReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray bytes = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(bytes);
    ui->pictureLabel->setPixmap(pixmap);
    reply->deleteLater();
}
