#include "addrec.h"
#include "ui_addrec.h"

AddRec::AddRec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRec)
{
    ui->setupUi(this);
}

AddRec::~AddRec()
{
    delete ui;
}