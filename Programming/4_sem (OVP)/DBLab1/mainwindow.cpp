#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase(this);
    db->connectToDataBase(":memory:");

    QSqlQuery query;
    query.exec("insert into Faculty values(1, 'MTS', '1', '4')");
    query.exec("insert into Faculty values(2, 'IVT', '2', '10')");
    query.exec("insert into Faculty values(3, 'AES', '3', '6')");

    query.exec("insert into Groups values(11, 'R-31', 'Petrov', '17', 1)");
    query.exec("insert into Groups values(12, 'R-32', 'Ivanov', '20', 1)");
    query.exec("insert into Groups values(13, 'R-33', 'Sidorov', '18', 1)");

    query.exec("insert into Students values(111, 'Filippov', 'Nekrasova', '321-31-12', 11)");
    query.exec("insert into Students values(112, 'Mazunin', 'Kirova', '343-32-54', 11)");
    query.exec("insert into Students values(113, 'Fedorinin', 'Vybornaya', '345-32-23', 11)");

    mod_Fc = new QSqlRelationalTableModel(this);
    mod_Fc->setTable("Faculty");
    mod_Fc->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    mod_Fc->setHeaderData(1, Qt::Horizontal, QObject::tr("Faculty"));
    mod_Fc->setHeaderData(2, Qt::Horizontal, QObject::tr("Year"));
    mod_Fc->setHeaderData(3, Qt::Horizontal, QObject::tr("Number of groups"));
    mod_Fc->select();
    mod_Fc->setEditStrategy(QSqlTableModel::OnFieldChange);
    mod_Gr = new QSqlRelationalTableModel(this);
    mod_Gr->setTable("Groups");
    mod_Gr->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    mod_Gr->setHeaderData(1, Qt::Horizontal, QObject::tr("Group_name"));
    mod_Gr->setHeaderData(2, Qt::Horizontal, QObject::tr("Name of elder"));
    mod_Gr->setHeaderData(3, Qt::Horizontal, QObject::tr("Number of students"));
    mod_Gr->setHeaderData(4, Qt::Horizontal, QObject::tr("Faculty ID"));
    mod_Gr->setRelation(4, QSqlRelation("Faculty", "id", "Faculty"));
    mod_Gr->select();
    mod_Gr->setEditStrategy(QSqlTableModel::OnFieldChange);
    mod_St = new QSqlRelationalTableModel(this);
    mod_St->setTable("Students");
    mod_St->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    mod_St->setHeaderData(1, Qt::Horizontal, QObject::tr("Full name"));
    mod_St->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    mod_St->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone number"));
    mod_St->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_GR"));
    mod_St->setRelation(4, QSqlRelation("Groups", "id", "Group_name"));
    mod_St->select();
    mod_St->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->tableView_Fc->setModel(mod_Fc);
    ui->tableView_Gr->setModel(mod_Gr);
    ui->tableView_St->setModel(mod_St);

    lastOrder = Qt::DescendingOrder;

    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()),
            Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Sort_clicked()
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
