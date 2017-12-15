#include "page.h"
#include "ui_page.h"

Page::Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page)
{
    ui->setupUi(this);
}

Page::~Page()
{
    delete ui;
}
