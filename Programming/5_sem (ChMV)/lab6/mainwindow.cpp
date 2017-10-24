#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_remember_clicked()
{
    QMap<QString, QString> *map = new QMap<QString, QString>();
    map->insert("test", "test");
    Dialog *dial = new Dialog(map);
    dial->show();
}
