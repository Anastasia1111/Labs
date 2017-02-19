#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);

    labelX = new QLabel(this);
    labelY = new QLabel(this);
    statusBar()->addWidget(labelY);
    statusBar()->addWidget(labelX);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent* e)
{
    QPoint p = e->pos();
    QRect widgetRect = ui->graphicsView->rect();

    if(widgetRect.contains(p))
    {
        ui->graphicsView->grabMouse();
    }
    else
    {
        ui->graphicsView->releaseMouse();
    }
    labelX->setText("X=" + QString().setNum(e->x()));
    labelY->setText("Y=" + QString().setNum(e->y()));
}