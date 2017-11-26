#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

    ui->webView->load(QUrl("http://www.cyberforum.ru/"));

    manager = new QNetworkAccessManager(this);

    ui->webView->page()->setNetworkAccessManager(manager);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBack_triggered()
{
    ui->webView->back();
}

void MainWindow::on_actionForward_triggered()
{
    ui->webView->forward();
}

void MainWindow::on_actionReload_triggered()
{
    ui->webView->reload();
}

void MainWindow::on_actionStop_triggered()
{
    ui->webView->stop();
}

void MainWindow::on_webView_loadProgress(int progress)
{
    ui->statusBar->showMessage("Загрузка " + ui->webView->url().toString() + "...", 500);
}

void MainWindow::smartLoad(QString value)
{
    QString validLink = value;

    if (validLink.toLower().startsWith("http:\\") || validLink.toLower().startsWith("ftp:\\"))
        validLink = validLink.replace(":\\\\", "://");

    if (!validLink.toLower().startsWith("http") && !validLink.toLower().startsWith("ftp"))
        validLink = "http://" + validLink;

    ui->webView->load(validLink);

    ui->webView->page()->setNetworkAccessManager(manager);
}

void MainWindow::on_urlPath_returnPressed()
{
    smartLoad(ui->urlPath->text());
}

void MainWindow::on_webView_loadFinished(bool arg1)
{
    if (arg1)
        ui->urlPath->setText(ui->webView->url().toString());
}

void MainWindow::replyFinished()
{
    if (reply->error() == QNetworkReply:: NoError)
    {
        QByteArray content = reply->readAll();
        QTextCodec *codec = QTextCodec::codecForName("cp1251");
        ui->textEdit->setPlainText(codec->toUnicode(content.data()));
        ui->webView->setHtml(ui->textEdit->toPlainText());
    } else
        qDebug() << reply->errorString();

    reply->deleteLater();
}

void MainWindow::on_pushButtonPOST_clicked()
{
    QUrl urlDoLogin("http://www.cyberforum.ru/log-in.php");
    QByteArray postData;
    postData+= "vb_login_username=" + QUrl::toPercentEncoding(QString("wiwopamuko@p33.org").toUtf8());
    postData+= "&cookieuser=1";
    postData+= "&vb_login_password="+ QUrl::toPercentEncoding(QString("71yH@V").toUtf8());
    postData+= "&s=&securitytoken=guest";
    postData+= "&do=login";
    postData+= "&vb_login_md5password=";
    postData+= "&vb_login_md5password_utf=";

    QNetworkRequest request(urlDoLogin);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Accept-Encoding", "identity");

    qDebug() << "url: " << urlDoLogin << ", post data: " << postData;

    reply = manager->post(request, postData);

    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void MainWindow::on_pushButtonGET_clicked()
{
    QUrl urlUser("http://www.cyberforum.ru/usercp.php");

    QNetworkRequest request(urlUser);
    request.setRawHeader("Accept-Encoding","identity");

    reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void MainWindow::on_webView_linkClicked(const QUrl &arg1)
{
    ui->urlPath->setText(arg1.toString());
    ui->webView->load(arg1);
}
