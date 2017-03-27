#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel;
    model->setRootPath("");
    ui->driveComboBox->setModel(model);
    ui->treeView->setModel(model);

    ui->treeView->setColumnWidth(0, ui->treeView->width()*4);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    connect(ui->driveComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setIndexChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setIndexChanged(int num)
{
    ui->treeView->setRootIndex(model->index(num,0));
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QFileSystemModel* subModel = new QFileSystemModel;
    qDebug() << index.child(0,0).data();
    //subModel->setRootPath(index.data())
    //ui->listWidget->addItems();
}
