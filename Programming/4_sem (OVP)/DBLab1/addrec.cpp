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

QString AddRec::data()
{
    QString data = "null, '"+
            ui->lineEdit_2->text()+
            "', '"+
            ui->lineEdit_3->text()+
            "', '"+
            ui->lineEdit_4->text()+
            "', ";
    if (ui->lineEdit_5->text().isEmpty())
        data += "null";
    else
        data += ui->lineEdit_5->text();
    return data;
}