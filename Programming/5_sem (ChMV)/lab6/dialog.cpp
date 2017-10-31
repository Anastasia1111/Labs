#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QMap<QPair<QString, QString>, QPair<QString, QString> > *map, QWidget *parent) :
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
    bool flag = false;
    typedef QPair<QString, QString> item_type;
    foreach (item_type item, map->keys()) {
        if(ui->linelogin->text() == item.first)
        {
            flag = true;
            login = item.first;
            password = item.second;
            question = map->find(item).value().first;
            answer = map->find(item).value().second;
            break;
        }
    }
    if (flag)
    {
        ui->question->setText(question);
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

void Dialog::on_linequestion_editingFinished()
{
    bool flag = false;
    if (ui->linequestion->text() == answer)
        flag = true;
    if (flag)
    {
        ui->pass->setText(password);
        ui->finish->show();
    } else {
        ui->pass->setText("Incorrect answer");
        ui->finish->hide();
    }
    ui->pass->show();
}

void Dialog::on_finish_clicked()
{
    this->accept();
}
