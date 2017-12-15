#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    name = husband = wife = "";
    date = QDate::currentDate();
    bougette = 1000;

    ui->dateEdit->setMinimumDate(date);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    name = ui->nameEdit->text();
    date = ui->dateEdit->date();
    bougette = ui->bougetteEdit->value();
    husband = ui->husbandEdit->text();
    wife = ui->wifeEdit->text();
}
