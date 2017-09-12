#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QWidget *wid = new QWidget(this);
    wid->setGeometry(20,20,80,80);
    QPalette *p = new QPalette(Qt::green);
    wid->setPalette(*p);
    wid->setAutoFillBackground(true);

    QLabel *l = new QLabel(this);
    l->setGeometry(80, 80, 300, 250);
    QPalette *p2 = new QPalette(Qt::gray);
    l->setPalette(*p2);
    l->setAutoFillBackground(true);
    l->setText("<H2><I><B>Happy birthday to:</H2></I></B>"
               "<P>"
               "<ul>"
               "<li>You</li>"
               "<li>Me</li>"
               "<li>All</li>"
               "</ul>"
               "<P>"
               "<table border=\"1\">"
               "<tr>"
               "<td>I wish you:</td><td>ShastiyaZdorovia</td>"
               "</tr>"
               "</table>"
               "<P>"
               "<img src =\"C:\\Users\\student\\Pictures\\hello.png\" width=\"100\" height=\"100\">");
    l->setStyleSheet("color:blue; font:italic");
    l->show();
}

Widget::~Widget()
{
    delete ui;
}
