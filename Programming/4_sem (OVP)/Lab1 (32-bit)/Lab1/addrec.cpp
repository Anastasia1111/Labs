#include "addrec.h"
#include "ui_addrec.h"

AddRec::AddRec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRec)
{
    ui->setupUi(this);
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

AddRec::~AddRec()
{
    delete ui;
}

QString AddRec::text()
{
    return ui->lineEdit->text();
}

bool AddRec::isFirstSectionSelected()
{
    return ui->radioButton_section1->isChecked();
}

bool AddRec::isSecondSectionSelected()
{
    return !isFirstSectionSelected();
}