#include "dbwindow.h"
#include "ui_dbwindow.h"

DBWindow::DBWindow(bool adminAccess, QWidget *parent) :
    QMainWindow(parent),
    adminAccess(adminAccess),
    ui(new Ui::DBWindow)
{
    ui->setupUi(this);
}

DBWindow::~DBWindow()
{
    delete ui;
}

void DBWindow::on_actionExit_triggered()
{
    ((QWidget *) this->parent())->show();
    this->close();
}
