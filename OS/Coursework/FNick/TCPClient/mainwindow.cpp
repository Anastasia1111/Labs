#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReady()));
    connect(socket, SIGNAL(connected()), this, SLOT(onConnect()));
}

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    socket->connectToHost(ui->serverLineEdit->text(), 1337);
}

void MainWindow::on_sayButton_clicked()
{
    QString msg = ui->sayLineEdit->text().trimmed();

    if (!msg.isEmpty())
        socket->write(msg.append('\n').toUtf8());

    ui->sayLineEdit->clear();
    ui->sayLineEdit->setFocus();
}

void MainWindow::onReady()
{
    while (socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        QRegExp msgRegex("^([^:]+):(.*)$");
        QRegExp usersRegex("^/users:(.*)$");

        if(usersRegex.indexIn(line) != -1)
        {
            QStringList users = usersRegex.cap(1).split(",");
            ui->userListWidget->clear();
            foreach(QString user, users)
                new QListWidgetItem(user, ui->userListWidget);
        }
        else if(msgRegex.indexIn(line) != -1)
        {
            QString user = msgRegex.cap(1);
            QString msg = msgRegex.cap(2);

            ui->roomTextEdit->append("<b>" + user + "</b>: " + msg);
        }
    }
}

void MainWindow::onConnect()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
    socket->write(QString("/me:" + ui->userLineEdit->text() + "\n").toUtf8());
}
