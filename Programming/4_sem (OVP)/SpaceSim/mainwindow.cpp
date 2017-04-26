#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // create our object and add it to the scene
    item = new MyItem();
    scene->addItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}
