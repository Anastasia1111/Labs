#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    db = new DataBase(this);
    db->connectToDataBase("/home/fnick/Repositories/Labs/Programming/5_sem (ChMV)/resources/databases/db1.db");

    wedMod = new QSqlRelationalTableModel();
    wedMod->setTable("Weddings");
    wedMod->setHeaderData(1, Qt::Horizontal, QObject::tr("Название свадьбы"));
    wedMod->setHeaderData(2, Qt::Horizontal, QObject::tr("Дата проведения"));
    wedMod->setHeaderData(3, Qt::Horizontal, QObject::tr("Бюджет"));
    wedMod->setHeaderData(4, Qt::Horizontal, QObject::tr("Жених"));
    wedMod->setHeaderData(5, Qt::Horizontal, QObject::tr("Невеста"));
    wedMod->setRelation(4, QSqlRelation("People", "id", "FullName"));
    wedMod->setRelation(5, QSqlRelation("People", "id", "FullName"));
    wedMod->select();
    ui->tableView->setModel(wedMod);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    evMod = new QSqlRelationalTableModel();
    evMod->setTable("Events");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOrganize_clicked()
{
    Dialog *dial = new Dialog(this);
    if (dial->exec() == QDialog::Accepted && !(dial->name == "" || dial->husband == "" || dial->wife == ""))
    {
        QSqlTableModel *pMod = new QSqlTableModel();
        int husband, wife;
        QSqlQuery query;
        query.exec(QString("insert into People values(null, '%1')").arg(dial->husband));
        query.exec(QString("insert into People values(null, '%1')").arg(dial->wife));
        pMod->setTable("People");
        pMod->select();
        for (int i = 0; i < pMod->rowCount(); ++i)
        {
            if (pMod->record(i).value(1).toString() == dial->husband) husband = pMod->record(i).value(0).toInt();
            if (pMod->record(i).value(1).toString() == dial->wife) wife = pMod->record(i).value(0).toInt();
        }
        QString rec = QString("insert into Weddings values(null, '%1', '%2', %3, %4, %5)")
                .arg(dial->name)
                .arg(dial->date.toString("yyyy-MM-dd"))
                .arg(dial->bougette)
                .arg(husband)
                .arg(wife);
        query.exec(rec);
        qDebug() << QString("new wedding (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        wedMod->select();
        on_tableView_doubleClicked(wedMod->index(wedMod->rowCount() - 1, 0));
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    curWedding = index;

    int id = wedMod->index(index.row(), 0).data().toInt();
    QDate date = QDate::fromString(wedMod->index(index.row(), 2).data().toString(), "yyyy-MM-dd");
    int bougette = wedMod->index(index.row(), 3).data().toInt();

    if (date >= QDate::currentDate())
        editMode = true;
    else
        editMode = false;

    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->clear();
    evIndex.clear();
    evMod->select();
    for (int i = 0; i < evMod->rowCount(); ++i)
    {
        if (evMod->record(i).value(6).toInt() == id)
        {
            Page *page = new Page(editMode, bougette, evMod->record(i), this);
            ui->tabWidget->addTab(page, evMod->record(i).value(1).toString());
            evIndex.insert(ui->tabWidget->count() - 1, evMod->record(i).value(0).toInt());

            connect(page, SIGNAL(nameChanged(QString)), this, SLOT(nameChange(QString)));
            connect(page, SIGNAL(bougetteChanged()), this, SLOT(updateUsedBougette()));
            connect(this, SIGNAL(usedBougetteUpdated(int)), page, SLOT(setUsedBougette(int)));
        }
    }
    if (ui->tabWidget->count() == 0)
    {
        QSqlQuery query;
        query.exec(QString("insert into Events values(null, 'Мероприятие', '', '00:00:00', 0, '', %1)").arg(id));
        qDebug() << QString("event for new wedding (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        evMod->select();
        Page *page = new Page(editMode, bougette, evMod->record(evMod->rowCount() - 1), this);
        ui->tabWidget->addTab(page, "Мероприятие");
        evIndex.insert(0, evMod->record(evMod->rowCount() - 1).value(0).toInt());

        connect(page, SIGNAL(nameChanged(QString)), this, SLOT(nameChange(QString)));
        connect(page, SIGNAL(bougetteChanged()), this, SLOT(updateUsedBougette()));
        connect(this, SIGNAL(usedBougetteUpdated(int)), page, SLOT(setUsedBougette(int)));
    }
    ui->buttonCancel->setHidden(ui->tabWidget->count() == 1 || !editMode);
    if (editMode) ui->tabWidget->addTab(new QWidget(), "+");
    updateUsedBougette();
}

void MainWindow::on_buttonBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    while (ui->tabWidget->count() != 0 && ui->tabWidget->tabText(0) != "+")
    {
        Page *wid = static_cast<Page*>(ui->tabWidget->widget(0));
        delete wid;
    }
}

void MainWindow::on_buttonDelete_clicked()
{
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); ++i)
    {
        int index = selectedList.at(i).row();
        QString id = wedMod->index(index, 0).data().toString();
        QDate date = QDate::fromString(wedMod->index(index, 2).data().toString(), "yyyy-MM-dd");
        if (date >= QDate::currentDate())
        {
            if (QMessageBox::warning(this, "Отмена свадьбы", "Вы уверены, что хотите отменить эту свадьбу?",
                                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QSqlQuery query;
                query.exec("delete from ParticipationOrganizations where ev_id in "
                           "(select id from Events where wed_id = " + id +")");
                qDebug() << QString("delete (%1): '%2' (%3)")
                            .arg(query.lastQuery())
                            .arg(query.lastError().text())
                            .arg(query.lastError().type() ? "not ok" : "ok");
                query.exec("delete from ParticipationPeople where ev_id in "
                           "(select id from Events where wed_id = " + id +")");
                qDebug() << QString("delete (%1): '%2' (%3)")
                            .arg(query.lastQuery())
                            .arg(query.lastError().text())
                            .arg(query.lastError().type() ? "not ok" : "ok");
                query.exec("delete from Items where ev_id in "
                           "(select id from Events where wed_id = " + id +")");
                qDebug() << QString("delete (%1): '%2' (%3)")
                            .arg(query.lastQuery())
                            .arg(query.lastError().text())
                            .arg(query.lastError().type() ? "not ok" : "ok");
                query.exec("delete from Events where wed_id = " + id);
                qDebug() << QString("delete (%1): '%2' (%3)")
                            .arg(query.lastQuery())
                            .arg(query.lastError().text())
                            .arg(query.lastError().type() ? "not ok" : "ok");
                query.exec("delete from Weddings where id = " + id);
                qDebug() << QString("delete (%1): '%2' (%3)")
                            .arg(query.lastQuery())
                            .arg(query.lastError().text())
                            .arg(query.lastError().type() ? "not ok" : "ok");
            }
        } else {
            QMessageBox *mb = new QMessageBox(QMessageBox::Warning, "Нелья отменить свадьбу", "Эта свадьба уже закончилась");
            mb->show();
        }
        wedMod->select();
    }
}

void MainWindow::nameChange(QString arg)
{
    int curTabIndex = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(curTabIndex, arg);
}

void MainWindow::updateUsedBougette()
{
    int id = wedMod->index(curWedding.row(), 0).data().toInt();
    int usedBougette = 0;
    evMod->select();
    for (int i = 0; i < evMod->rowCount(); ++i)
        if (evMod->record(i).value(6).toInt() == id)
            usedBougette += evMod->record(i).value(4).toInt();
    qDebug() << "used bougette now = " << usedBougette;
    emit usedBougetteUpdated(usedBougette);
}

void MainWindow::on_buttonCancel_clicked()
{
    if (QMessageBox::warning(this, "Отмена мероприятия", "Вы уверены, что хотите отменить это мероприятие?",
                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        int id = evIndex.value(ui->tabWidget->currentIndex());
        QSqlQuery query;
        query.exec(QString("delete from ParticipationOrganizations where ev_id = %1").arg(id));
        qDebug() << QString("delete (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        query.exec(QString("delete from ParticipationPeople where ev_id = %1").arg(id));
        qDebug() << QString("delete (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        query.exec(QString("delete from Items where ev_id = %1").arg(id));
        qDebug() << QString("delete (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        query.exec(QString("delete from Events where id = %1").arg(id));
        qDebug() << QString("cancel (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");
        Page *wid = static_cast<Page*>(ui->tabWidget->currentWidget());
        ui->tabWidget->removeTab(id);
        delete wid;
        ui->buttonCancel->setHidden(ui->tabWidget->count() == 2);
        ui->tabWidget->setCurrentIndex(0);
        updateUsedBougette();
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    int ind = ui->tabWidget->currentIndex();
    if (ui->tabWidget->tabText(index) == "+")
    {
        int id = wedMod->index(curWedding.row(), 0).data().toInt();
        QSqlQuery query;
        query.exec(QString("insert into Events values(null, 'Мероприятие', '', '00:00:00', 0, '', %1)").arg(id));
        qDebug() << QString("new event (%1): '%2' (%3)")
                    .arg(query.lastQuery())
                    .arg(query.lastError().text())
                    .arg(query.lastError().type() ? "not ok" : "ok");

        int bougette = wedMod->index(curWedding.row(), 3).data().toInt();
        evMod->select();
        Page *page = new Page(true, bougette, evMod->record(evMod->rowCount() - 1), this);
        ui->tabWidget->insertTab(ind + 1, page, "Мероприятие");
        evIndex.insert(ui->tabWidget->count() - 1, evMod->record(evMod->rowCount() - 1).value(0).toInt());

        connect(page, SIGNAL(nameChanged(QString)), this, SLOT(nameChange(QString)));
        connect(page, SIGNAL(bougetteChanged()), this, SLOT(updateUsedBougette()));
        connect(this, SIGNAL(usedBougetteUpdated(int)), page, SLOT(setUsedBougette(int)));

        ui->tabWidget->setCurrentIndex(ind);
        updateUsedBougette();
    }
}
