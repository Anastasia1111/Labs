#include "page.h"
#include "ui_page.h"

Page::Page(bool editMode, int bougette, QSqlRecord record, QWidget *parent) :
    QWidget(parent),
    editMode(editMode),
    allBougette(bougette),
    ui(new Ui::Page)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    inConstruction = true;
    id = record.value(0).toInt();
    ui->nameEdit->setText(record.value(1).toString());
    ui->descriptionEdit->setPlainText(record.value(2).toString());
    ui->timeEdit->setTime(QTime::fromString(record.value(3).toString(), "hh:mm:ss"));
    ui->bougetteSpinBox->setValue(record.value(4).toInt());
    setPhoto(record.value(5).toString());
    inConstruction = false;
}

Page::~Page()
{
    delete ui;
}

void Page::on_navigationButton_clicked()
{
    int index = 1 - ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index);
    ui->navigationButton->setText(index ? "К описанию мероприятия" : "К перечням участников/предметов");
}

void Page::on_bougetteSpinBox_valueChanged(int arg1)
{
    price = arg1;
    ui->bougetteSpinBox->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("%1").arg(arg1), "Price");
}

void Page::on_photoButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Добавить фотографию"),
                                                "/home",
                                                tr("Images (*.png *.xpm *.jpg)"));
    if (path != "")
        setPhoto(path);
}

void Page::updateRecord(QString value, QString field)
{
    QSqlQuery query;
    query.exec(QString("update Events set %1 = %2 where id = %3").arg(field).arg(value).arg(id));
    qDebug() << QString("update (%1): '%2' (%3)")
                .arg(query.lastQuery())
                .arg(query.lastError().text())
                .arg(query.lastError().type() ? "not ok" : "ok");
}

QString Page::getName() const
{
    return name;
}

void Page::setPhoto(const QString &value)
{
    photo = value;
    ui->photoLabel->setPixmap(QPixmap(value));
    ui->photoButton->setHidden(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(value), "Photo");
}

void Page::on_nameEdit_textChanged(const QString &arg1)
{
    name = arg1;
    ui->nameEdit->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(arg1), "Name");
    emit nameChanged(arg1);
}

void Page::on_descriptionEdit_textChanged()
{
    descr = ui->descriptionEdit->toPlainText();
    ui->descriptionEdit->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(descr), "Description");
}

void Page::on_timeEdit_timeChanged(const QTime &time)
{
    this->time = time;
    ui->timeEdit->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(time.toString("hh:mm:ss")), "Time");
}
