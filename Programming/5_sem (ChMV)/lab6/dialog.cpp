#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QMap<QString, QString>* map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    map(map)
{
    ui->setupUi(this);
    ui->pass->hide();
    ui->question->hide();
    ui->linequestion->hide();
    ui->finish->hide();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_linelogin_editingFinished()
{
    bool flag1 = false;
    foreach (QString item, map->keys()) {
        if(ui->linelogin->text() == item)
            flag1 = true;
    }
    if (flag1)
    {
        ui->question->setText("Test question");
        ui->linequestion->show();
        ui->pass->hide();
        ui->finish->hide();
    } else {
        ui->question->setText("Incorrect login");
        ui->linequestion->hide();
        ui->pass->hide();
        ui->finish->hide();
    }
    ui->question->show();
}
