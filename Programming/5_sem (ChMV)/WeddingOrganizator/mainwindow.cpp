#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase(this);
    db->connectToDataBase("/home/fnick/chmvCurs/resources/database/db1.db");
}

MainWindow::~MainWindow()
{
    delete ui;
}
