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

float func(int n)
{
    float i = 5.2, h;
    h = i*i/n;
    return h;
}

void MainWindow::on_pushButton_clicked()
{
    int n = ui->lineEdit_2->text().toUInt();
    ui->lineEdit->setText(QString::number(func(n)));
    qDebug()<<func(n);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str;
    int n = ui->lineEdit_3->text().toUInt();
    int** a = new int*[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand()%(2*n)-n;
            str.append(QString("%1  ").arg(a[i][j]));
        }
        str.append(QString("\n"));
    }
    ui->text->append(str);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->text->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
}
