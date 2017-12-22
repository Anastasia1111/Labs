#include "page.h"
#include "ui_page.h"

Page::Page(bool editMode, int bougette, QSqlRecord record, QWidget *parent) :
    QWidget(parent),
    editMode(editMode),
    bougette(bougette),
    record(record),
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

    itemMod = new QSqlQueryModel();
    itemMod->setQuery(QString("select id, Name from Items where ev_id = %1").arg(id));
    ui->itemList->setModel(itemMod);
    ui->itemList->setModelColumn(1);
    ui->itemButtonBox->setHidden(!editMode);
    peopleMod = new QSqlQueryModel();
    peopleMod->setQuery(QString("select id, FullName from People where id in "
                              "(select p_id from ParticipationPeople where ev_id = %1)").arg(id));
    ui->peopleList->setModel(peopleMod);
    ui->peopleList->setModelColumn(1);
    ui->peopleButtonBox->setHidden(!editMode);
    orgMod = new QSqlQueryModel();
    orgMod->setQuery(QString("select id, Name from Organizations where id in "
                             "(select org_id from ParticipationOrganizations where ev_id = %1)").arg(id));
    ui->orgList->setModel(orgMod);
    ui->orgList->setModelColumn(1);
    ui->orgButtonBox->setHidden(!editMode);

    qDebug() << "page " << record << " initialized";
}

Page::~Page()
{
    delete ui;
    qDebug() << "page " << record << " deleted";
}

void Page::on_navigationButton_clicked()
{
    int index = 1 - ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index);
    ui->navigationButton->setText(index ? "К описанию мероприятия" : "К перечням участников/предметов");
}

void Page::on_bougetteSpinBox_valueChanged(int arg1)
{
    ui->bougetteSpinBox->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("%1").arg(arg1), "Price");
    emit bougetteChanged();
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

void Page::setPhoto(const QString &value)
{
    ui->photoLabel->setPixmap(QPixmap(value));
    ui->photoButton->setHidden(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(value), "Photo");
}

void Page::on_nameEdit_textChanged(const QString &arg1)
{
    ui->nameEdit->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(arg1), "Name");
    emit nameChanged(arg1);
}

void Page::on_descriptionEdit_textChanged()
{
    ui->descriptionEdit->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(ui->descriptionEdit->toPlainText()), "Description");
}

void Page::on_timeEdit_timeChanged(const QTime &time)
{
    ui->timeEdit->setReadOnly(!editMode);
    if (!inConstruction) updateRecord(QString("'%1'").arg(time.toString("hh:mm:ss")), "Time");
}

void Page::setUsedBougette(int value)
{
    ui->bougetteLabel->setText(QString("Бюджет: %1/%2").arg(value).arg(bougette));
    ui->bougetteSpinBox->setMaximum(bougette - (value - ui->bougetteSpinBox->value()));
}

void Page::on_itemAddButton_clicked()
{
    QString name = QInputDialog::getText(this, "Добавить вещь", "Название вещи:");
    if (name != "")
    {
        QSqlQuery query;
        query.exec(QString("insert into Items values(null, '%1', %2)").arg(name).arg(id));
        qDebug() << QString("new item (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        itemMod->setQuery(QString("select id, Name from Items where ev_id = %1").arg(id));
    }
}

void Page::on_itemRemoveButton_clicked()
{
    QModelIndexList selectedList = ui->itemList->selectionModel()->selectedIndexes();
    for (int i = 0; i < selectedList.count(); ++i)
    {
        int index = selectedList.at(i).row();
        QString it_id = itemMod->index(index, 0).data().toString();
        QSqlQuery query;
        query.exec("delete from Items where id = " + it_id);
        qDebug() << QString("delete (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        itemMod->setQuery(QString("select id, Name from Items where ev_id = %1").arg(id));
    }
}

void Page::on_peopleAddButton_clicked()
{
    QString name = QInputDialog::getText(this, "Добавить участника", "ФИО участника:");
    if (name != "")
    {
        QSqlQuery query;
        query.exec(QString("insert into People values(null, '%1')").arg(name));
        qDebug() << QString("new guest (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        peopleMod->setQuery("select id, FullName from People");
        for (int i = 0; i < peopleMod->rowCount(); ++i)
        {
            if (peopleMod->record(i).value(1).toString() == name)
            {
                query.exec(QString("insert into ParticipationPeople values(%1, %2)")
                           .arg(peopleMod->record(i).value(0).toInt())
                           .arg(id));
                qDebug() << QString("new guest (%1): '%2' (%3)")
                            .arg(query.lastQuery())
                            .arg(query.lastError().text())
                            .arg(query.lastError().type() ? "not ok" : "ok");
                break;
            }
        }
        peopleMod->setQuery(QString("select id, FullName from People where id in "
                                  "(select p_id from ParticipationPeople where ev_id = %1)").arg(id));
    }
}

void Page::on_peopleRemoveButton_clicked()
{
    QModelIndexList selectedList = ui->peopleList->selectionModel()->selectedIndexes();
    for (int i = 0; i < selectedList.count(); ++i)
    {
        int index = selectedList.at(i).row();
        QString p_id = peopleMod->index(index, 0).data().toString();
        QSqlQuery query;
        query.exec(QString("delete from ParticipationPeople where p_id = %1 and ev_id = %2").arg(p_id).arg(id));
        qDebug() << QString("delete (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        peopleMod->setQuery(QString("select id, FullName from People where id in "
                                  "(select p_id from ParticipationPeople where ev_id = %1)").arg(id));
    }
}

void Page::on_orgAddButton_clicked()
{
    QString name = QInputDialog::getText(this, "Добавить организацию", "Название организации");
    if (name != "")
    {
        QSqlQuery query;
        query.exec(QString("insert into Organizations values(null, '%1')").arg(name));
        qDebug() << QString("new org (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        orgMod->setQuery("select id, Name from Organizations");
        for (int i = 0; i < orgMod->rowCount(); ++i)
        {
            if (orgMod->record(i).value(1).toString() == name)
            {
                query.exec(QString("insert into ParticipationOrganizations values(%1, %2)")
                           .arg(orgMod->record(i).value(0).toInt())
                           .arg(id));
                qDebug() << QString("new org (%1): '%2' (%3)")
                            .arg(query.lastQuery())
                            .arg(query.lastError().text())
                            .arg(query.lastError().type() ? "not ok" : "ok");
                break;
            }
        }
        orgMod->setQuery(QString("select id, Name from Organizations where id in "
                                 "(select org_id from ParticipationOrganizations where ev_id = %1)").arg(id));
    }
}

void Page::on_orgRemoveButton_clicked()
{
    QModelIndexList selectedList = ui->orgList->selectionModel()->selectedIndexes();
    for (int i = 0; i < selectedList.count(); ++i)
    {
        int index = selectedList.at(i).row();
        QString org_id = orgMod->index(index, 0).data().toString();
        QSqlQuery query;
        query.exec(QString("delete from ParticipationOrganizations where org_id = %1 and ev_id = %2").arg(org_id).arg(id));
        qDebug() << QString("delete (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        orgMod->setQuery(QString("select id, Name from Organizations where id in "
                                 "(select org_id from ParticipationOrganizations where ev_id = %1)").arg(id));
    }
}
