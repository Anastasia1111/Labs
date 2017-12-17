#include "page.h"
#include "ui_page.h"

Page::Page(bool editMode, int bougette, QWidget *parent) :
    QWidget(parent),
    editMode(editMode),
    allBougette(bougette),
    ui(new Ui::Page)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->nameEdit->setReadOnly(true);
    ui->nameEdit->setText("Name");
}

Page::~Page()
{
    delete ui;
}

void Page::on_navigationButton_clicked()
{
    int index = 1 - ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index);
    ui->navigationButton->setText(index ? "Назад" : "Вперед");
}

void Page::on_bougetteSpinBox_valueChanged(int arg1)
{
    ui->bougetteLabel->setText(QString("Бюджет: %1/%2").arg(arg1).arg(allBougette));
}

void Page::on_photoButton_clicked()
{

}

void Page::on_nameEdit_editingFinished()
{
    //name = ui->nameEdit->text();
}
