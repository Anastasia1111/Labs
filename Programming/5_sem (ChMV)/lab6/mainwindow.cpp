#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelWrong->hide();

    db = new DataBase(this);
    db->connectToDataBase("..\\..\\resources\\databases\\lab1.sqlite");

    map = new QMap< QPair<QString, QString>, QPair<QString, QString> >();
    this->updateMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_remember_clicked()
{
    Dialog *dial = new Dialog(map);
    dial->show();
}

void MainWindow::on_pushButtonNext_clicked()
{
    bool flag = false;
    typedef QPair<QString, QString> item_type;
    foreach (item_type item, map->keys()) {
        if(ui->linelogin->text() == item.first)
        {
            if (ui->linepass->text() == item.second)
            {
                flag = true;
            }
            break;
        }
    }
    if (!flag)
    {
        ui->labelWrong->show();
        return;
    }

    DBWindow* win = new DBWindow(ui->linelogin->text(), ui->linepass->text(), db->getDB(), this);
    win->show();
    this->hide();

    ui->labelWrong->hide();

    connect(win, SIGNAL(newUserAdded()), this, SLOT(updateMap()));
}

void MainWindow::on_linelogin_editingFinished()
{
    if(ui->linepass->text() == "")
        ui->linepass->setFocus();
}

void MainWindow::on_linepass_editingFinished()
{
    if(ui->linelogin->text() == "")
        ui->linelogin->setFocus();
}

void MainWindow::updateMap()
{
    QSqlQuery* query = new QSqlQuery(db->getDB());
    query->exec("SELECT " TABLE2_LOG ", " TABLE2_PAS ", " TABLE2_QST ", " TABLE2_ANS " FROM " TABLE2);
    if (!query->isActive())
        QMessageBox::warning(
                    this,
                    tr("Database Error"),
                    query->lastError().text()
        );
    while (query->next())
    {
        QString log = Crypter::decryptString(query->value(0).toString());
        QString pas = Crypter::decryptString(query->value(1).toString());
        QPair<QString, QString>* logNpass = new QPair<QString, QString>(log, pas);
        QString qst = Crypter::decryptString(query->value(2).toString());
        QString ans = Crypter::decryptString(query->value(3).toString());
        QPair<QString, QString>* questNans = new QPair<QString, QString>(qst, ans);
        map->insert(*logNpass, *questNans);
        qDebug() << log << " " << pas << " " << qst << " " << ans << endl;
    }
}
