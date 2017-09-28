#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auth.h"
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action,SIGNAL(triggered()),this,SLOT(About_Lab1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QTextCharFormat format;
    for(int i = 0; i < 5; i++)
    {
        format.setForeground(qvariant_cast<QColor>("black"));
        ui->calendarWidget->setWeekdayTextFormat(Qt::DayOfWeek(i+1), format);
    }
    for(int i = 5; i < 7; i++)
    {
        format.setForeground(qvariant_cast<QColor>("red"));
        ui->calendarWidget->setWeekdayTextFormat(Qt::DayOfWeek(i+1), format);
    }
    ui->calendarWidget->setFirstDayOfWeek(Qt::DayOfWeek(index+1));
    format.setForeground(qvariant_cast<QColor>("green"));
    ui->calendarWidget->setWeekdayTextFormat(Qt::DayOfWeek(index+1), format);
}

void MainWindow::About_Lab1()
{
    auth *dg = new auth();
    dg->show();
}
