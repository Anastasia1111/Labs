#include "winchange.h"
#include "ui_winchange.h"

WinChange::WinChange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinChange)
{
    ui->setupUi(this);

    connect(ui->pushButton_Change, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

WinChange::~WinChange()
{
    delete ui;
}

qint32 WinChange::width()
{
    return ui->lineEdit_Width->text().toInt();
}

qint32 WinChange::height()
{
    return ui->lineEdit_Height->text().toInt();
}

qint32 WinChange::stars()
{
    return ui->lineEdit_Stars->text().toInt();
}