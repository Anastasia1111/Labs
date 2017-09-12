#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <QPalette>
#include <QLCDNumber>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Движок");
    QPushButton *but = new QPushButton();
    QVBoxLayout *layout = new QVBoxLayout();
    QPalette *pal = new QPalette();
    QLCDNumber *num = new QLCDNumber();
    QSlider *sl = new QSlider(Qt::Horizontal);

    pal->setColor(QPalette::ButtonText, Qt::cyan);
    but->setPalette(*pal);
    but->setText("Quit");
    sl->setRange(0, 100);
    //num->setFixedSize(300, 300);
    num->setSegmentStyle(QLCDNumber::Filled);

    connect(sl, SIGNAL(valueChanged(int)), num, SLOT(display(int)));
    connect(but, SIGNAL(clicked()), this, SLOT(close()));

    layout->addWidget(but);
    layout->addWidget(num);
    layout->addWidget(sl);
    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
