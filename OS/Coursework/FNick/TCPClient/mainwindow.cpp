#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    partner = NULL;
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    ui->actionDisconnect->setVisible(false);

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
    if (ui->serverLineEdit->text() == "lh")
        ui->serverLineEdit->setText("localhost");
    socket->connectToHost(ui->serverLineEdit->text(), 1337);
    if (!socket->waitForConnected(1000))
        ui->errLabel->setText(QString("Can't establish connection! (Error code: %1)").arg(socket->error()));
}

void MainWindow::on_sayButton_clicked()
{
    QString msg = ui->sayLineEdit->text().trimmed();

    if (!msg.isEmpty())
    {
        if (partner != NULL)
            msg = "/to:" + partner->text() + ", " + msg;
        socket->write(msg.append('\n').toUtf8());
    }

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

        if(usersRegex.indexIn(line) != -1) // Если это список юзеров
        {
            QStringList users = usersRegex.cap(1).split(",");
            ui->userListWidget->clear();
            foreach(QString user, users)
                new QListWidgetItem(user, ui->userListWidget);
        }
        else if(msgRegex.indexIn(line) != -1) // Если это нормальное сообщение
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
    ui->actionDisconnect->setVisible(true);
    socket->write(QString("/me:" + ui->userLineEdit->text() + "\n").toUtf8());
}

void MainWindow::on_actionDisconnect_triggered()
{
    socket->disconnectFromHost();
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_sayLineEdit_returnPressed()
{
    on_sayButton_clicked();
}

void MainWindow::on_userListWidget_itemClicked(QListWidgetItem *item)
{
    if (partner != item)
    {
        partner = item;
        qDebug() << "Private target: " << item->text();
    } else {
        partner = NULL;
        ui->userListWidget->clearSelection();
        qDebug() << "Private target: none";
    }
}
