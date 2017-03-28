#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    baseModel = new QFileSystemModel;
    baseModel->setRootPath("");
    fileModel = new QFileSystemModel;
    fileModel->setRootPath("");
    ui->driveComboBox->setModel(baseModel);
    ui->treeView->setModel(baseModel);
    ui->listView->setModel(fileModel);

    ui->treeView->setColumnWidth(0, ui->treeView->width()*4);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    fileModel->setNameFilterDisables(false);

    timeTracking = false;
    labelPath = new QLabel("path", this);
    labelNameSize = new QLabel("filename,filesize", this);
    labelTime = new QLabel("current_time", this);
    statusBar()->addWidget(labelPath);
    statusBar()->addWidget(labelNameSize);
    statusBar()->addPermanentWidget(labelTime);

    connect(ui->driveComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setIndexChanged(int)));

    startTimer(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* e)
{
    if(timeTracking){
        QTime time = QTime::currentTime();
        labelTime->setText(time.toString());
    }
}

void MainWindow::setIndexChanged(int num)
{
    ui->treeView->setRootIndex(baseModel->index(num,0));
    ui->listView->setRootIndex(fileModel->index(num,0));
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString filter = ui->filterComboBox->currentText();

    ui->listView->setRootIndex(fileModel->index(baseModel->filePath(index)));

    if (filter == "All files (*.*)")
        fileModel->setNameFilters(QStringList("*.*"));
    if (filter == "Bitmap Image (*.bmp)")
        fileModel->setNameFilters(QStringList("*.bmp"));
    if (filter == "PNG Image (*.png)")
        fileModel->setNameFilters(QStringList("*.png"));
    if (filter == "JPEG Image (*.jpg)")
        fileModel->setNameFilters(QStringList("*.jpg"));
}

void MainWindow::on_filterComboBox_currentIndexChanged(int index)
{
    this->on_treeView_clicked(ui->treeView->selectionModel()->currentIndex());
}

void MainWindow::on_pushButton_clicked()
{
    timeTracking = !timeTracking;
    labelTime->setText("current_time");
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString fPath = fileModel->filePath(index);
    labelPath->setText(fPath);
    labelNameSize->setText(fileModel->fileName(index)+", "+QString::number(fileModel->fileInfo(index).size())+" byte");
    QPixmap img(fPath);
    if (!img.isNull())
    {
        if(img.height()>ui->graphicsView->height()) img = img.scaledToHeight(ui->graphicsView->height());
        if(img.width()>ui->graphicsView->width()) img = img.scaledToWidth(ui->graphicsView->width());
        QGraphicsScene* scene = new QGraphicsScene();
        scene->setSceneRect(ui->graphicsView->rect());
        scene->addPixmap(img);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
    }
}
