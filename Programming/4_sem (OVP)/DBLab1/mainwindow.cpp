#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(":memory:");

    QFileInfo checkFile(filename);

    if (db.open()) {
        qDebug() << "[+] Connected to Database File";
    }
    else {
        qDebug() << "[!] Database \"File\" was not opened";
        qDebug() << db.lastError().text();
    }

    QSqlQuery query;
    query.exec("create table Факультет (Код int primary key,"
                                        "Факультет varchar(20),"
                                        "Курс varchar(20),"
                                        "Количество групп varchar(20))");
    query.exec("insert into Факультет values(1, 'МТС', '1', '4')");
    query.exec("insert into Факультет values(2, 'ИВТ', '2', '10')");
    query.exec("insert into Факультет values(3, 'АЭС', '3', '6')");

    query.exec("create table Группа (Код int primary key,"
                                     "Название группы varchar(20),"
                                     "Фамилия старосты varchar(20),"
                                     "Количество varchar(20),"
                                     "Факультет int)");
    query.exec("insert into Группа values(11, 'Р-31', 'Петров', '17', 1)");
    query.exec("insert into Группа values(12, 'Р-32', 'Иванов', '20', 1)");
    query.exec("insert into Группа values(13, 'Р-33', 'Сидоров', '18', 1)");


    query.exec("create table Студенты (Код int primary key,"
                                       "ФИО varchar(40),"
                                       "Адрес varchar(40),"
                                       "Телефон varchar(40),"
                                       "ID_GR int)");
    query.exec("insert into Студенты values(111, 'Филиппов Е.В.', 'Некрасова, 134', '321-31-12', 11)");
    query.exec("insert into Студенты values(112, 'Мазунин В.П.', 'Кирова, 117', '343-32-54', 11)");
    query.exec("insert into Студенты values(113, 'Федоринин А.В.', 'Выборная, 133', '345-32-23', 11)");

    QSqlRelationalTableModel* mod_Fc = new QSqlRelationalTableModel(0,db);
    mod_Fc->setTable("Факультет");
    mod_Fc->setHeaderData(0, Qt::Horizontal, QObject::tr("Код"));
    mod_Fc->setHeaderData(1, Qt::Horizontal, QObject::tr("Факультет"));
    mod_Fc->setHeaderData(2, Qt::Horizontal, QObject::tr("Курс"));
    mod_Fc->setHeaderData(3, Qt::Horizontal, QObject::tr("Количество групп"));
    mod_Fc->select();
    mod_Fc->setEditStrategy(QSqlTableModel::OnFieldChange);
    QSqlRelationalTableModel* mod_Gr = new QSqlRelationalTableModel(0,db);
    mod_Gr->setTable("Группа");
    mod_Gr->setHeaderData(0, Qt::Horizontal, QObject::tr("Код"));
    mod_Gr->setHeaderData(1, Qt::Horizontal, QObject::tr("Название группы"));
    mod_Gr->setHeaderData(2, Qt::Horizontal, QObject::tr("Фамилия старосты"));
    mod_Gr->setHeaderData(3, Qt::Horizontal, QObject::tr("Количество"));
    mod_Gr->setHeaderData(4, Qt::Horizontal, QObject::tr("Факультет ID"));
    mod_Gr->setRelation(4, QSqlRelation("Факультет", "Код", "Факультет"));
    mod_Gr->select();
    mod_Gr->setEditStrategy(QSqlTableModel::OnFieldChange);
    QSqlRelationalTableModel* mod_St = new QSqlRelationalTableModel(0,db);
    mod_St->setTable("Студенты");
    mod_St->setHeaderData(0, Qt::Horizontal, QObject::tr("Код"));
    mod_St->setHeaderData(1, Qt::Horizontal, QObject::tr("ФИО"));
    mod_St->setHeaderData(2, Qt::Horizontal, QObject::tr("Адрес"));
    mod_St->setHeaderData(3, Qt::Horizontal, QObject::tr("Телефон"));
    mod_St->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_GR"));
    mod_St->setRelation(4, QSqlRelation("Группа", "Код", "Название группы"));
    mod_St->select();
    mod_St->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->tableView_Fc->setModel(mod_Fc);
    ui->tableView_Gr->setModel(mod_Gr);
    ui->tableView_St->setModel(mod_St);

    lastOrder = Qt::DescendingOrder;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (lastOrder == Qt::AscendingOrder){
        ui->tableView_St->sortByColumn(1, Qt::DescendingOrder);
        lastOrder = Qt::DescendingOrder;
    } else {
        ui->tableView_St->sortByColumn(1, Qt::AscendingOrder);
        lastOrder = Qt::AscendingOrder;
    }
}

void MainWindow::on_lineEdit_CharSearch_textChanged(const QString &arg1)
{
    ui->tableView_St->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView_St->clearSelection();
    for (int i = 0; i < ui->tableView_St->model()->rowCount(); ++i){
        QString str = ui->tableView_St->model()->index(i,1).data().toString();
        if (str.contains(arg1) == true) ui->tableView_St->selectRow(i);
    }
    if (arg1 == "") ui->tableView_St->clearSelection();
}

void MainWindow::on_lineEdit_WordSearch_textChanged(const QString &arg1)
{
    ui->tableView_St->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView_St->clearSelection();
    for (int i = 0; i < ui->tableView_St->model()->rowCount(); ++i){
        QString str = ui->tableView_St->model()->index(i,1).data().toString();
        if (str == arg1) ui->tableView_St->selectRow(i);
    }
}
