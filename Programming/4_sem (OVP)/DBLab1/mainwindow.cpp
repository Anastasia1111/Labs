#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString lFileName = QFileDialog::getOpenFileName(this, "Open file...",
                        QDir::homePath(),"All files (*.*)");
    db.setDatabaseName(lFileName);
    if(!db.open()){
        qDebug() << db.lastError().text();
    }
    qDebug() << lFileName;
}

MainWindow::~MainWindow()
{
    delete ui;
}