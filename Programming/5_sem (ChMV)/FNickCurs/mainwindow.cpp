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
    wedMod->setHeaderData(4, Qt::Horizontal, QObject::tr("Муж"));
    wedMod->setHeaderData(5, Qt::Horizontal, QObject::tr("Жена"));
    wedMod->setRelation(4, QSqlRelation("People", "id", "FullName"));
    wedMod->setRelation(5, QSqlRelation("People", "id", "FullName"));
    wedMod->select();
    ui->tableView->setModel(wedMod);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    deleteMode = false;
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
        QSqlQuery hwQuery;
        hwQuery.exec(QString("insert into People values(null, '%1')").arg(dial->husband));
        hwQuery.exec(QString("insert into People values(null, '%1')").arg(dial->wife));
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
        QSqlQuery query;
        query.exec(rec);
        qDebug() << query.lastError();

        wedMod->select();
        on_tableView_doubleClicked(wedMod->index(wedMod->rowCount() - 1, 0));
    }
}

void MainWindow::on_actionOrganize_triggered()
{
    on_buttonOrganize_clicked();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int id = wedMod->index(index.row(), 0).data().toInt();
    QDate date = QDate::fromString(wedMod->index(index.row(), 2).data().toString(), "yyyy-MM-dd");
    int bougette = wedMod->index(index.row(), 3).data().toInt();

    if (date >= QDate::currentDate())
        editMode = true;
    else
        editMode = false;

    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->clear();
    QSqlTableModel *events = new QSqlTableModel();
    events->setTable("Events");
    events->select();
    for (int i = 0; i < events->rowCount(); ++i)
    {
        if (events->record(i).value(6).toInt() == id)
        {
            QString name = events->record(i).value(1).toString();
            QString description = events->record(i).value(2).toString();
            QTime time = QTime::fromString(events->record(i).value(3).toString(), "hh:mm:ss");
            int price = events->record(i).value(4).toInt();
            QPixmap pic = QPixmap(events->record(i).value(5).toString());
            Page *page = new Page(editMode, bougette, this);
            ui->tabWidget->addTab(page, name);
        }
    }
}

void MainWindow::on_buttonBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (ui->tabWidget->tabText(index) == "+")
        qDebug() << "Yep";
}

void MainWindow::on_buttonDelete_clicked()
{
    ui->buttonDelete->setChecked(!ui->buttonDelete->isChecked());
    deleteMode = !deleteMode;
    deleteMode ? ui->buttonDelete->setStyleSheet("color: red;") : ui->buttonDelete->setStyleSheet("color: black;");
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if (deleteMode)
    {
        QString id = wedMod->index(index.row(), 0).data().toString();
        QDate date = QDate::fromString(wedMod->index(index.row(), 2).data().toString(), "yyyy-MM-dd");
        if (date >= QDate::currentDate())
        {
            QSqlQuery delQuery;
            delQuery.exec("delete from Weddings where id = " + id);
            qDebug() << delQuery.lastQuery();
        } else {
            QMessageBox *mb = new QMessageBox(QMessageBox::Warning,"Нелья отменить свадьбу", "Эта свадьба уже закончилась");
            mb->show();
        }
        wedMod->select();
        on_buttonDelete_clicked();
    }
}
