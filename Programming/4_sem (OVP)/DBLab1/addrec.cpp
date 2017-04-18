#include "addrec.h"
#include "ui_addrec.h"

AddRec::AddRec(QString &name2, QString &name3, QString &name4, QString &name5, QSqlQueryModel *mod, QWidget *parent) :
    QDialog(parent),
    lmod(mod),
    fifthColumn(name5),
    ui(new Ui::AddRec)
{
    ui->setupUi(this);

    ui->label_2->setText(name2);
    ui->label_3->setText(name3);
    ui->label_4->setText(name4);
    ui->label_5->setText(name5);

    ui->comboBox->setModel(lmod);
    ui->comboBox->setModelColumn(1);

    if (fifthColumn == TABLE1_FAKE){
        ui->verticalLayout_5->removeWidget(ui->label_5);
        delete ui->label_5;
        ui->verticalLayout_5->removeWidget(ui->comboBox);
        delete ui->comboBox;
    }

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
    if (fifthColumn == TABLE1_FAKE || ui->comboBox->currentText().isEmpty())
        data += "null";
    else
        data += lmod->index(ui->comboBox->currentIndex(),0).data().toString();
    return data;
}