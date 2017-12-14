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

    mod = new QSqlRelationalTableModel();
    mod->setTable("Weddings");
    mod->setHeaderData(1, Qt::Horizontal, QObject::tr("Название свадьбы"));
    mod->setHeaderData(2, Qt::Horizontal, QObject::tr("Дата проведения"));
    mod->setHeaderData(3, Qt::Horizontal, QObject::tr("Бюджет"));
    mod->setHeaderData(4, Qt::Horizontal, QObject::tr("Муж"));
    mod->setHeaderData(5, Qt::Horizontal, QObject::tr("Жена"));
    mod->setRelation(4, QSqlRelation("People", "id", "FullName"));
    mod->setRelation(5, QSqlRelation("People", "id", "FullName"));
    mod->select();
    ui->tableView->setModel(mod);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOrganize_clicked()
{

}

void MainWindow::on_actionOrganize_triggered()
{
    on_buttonOrganize_clicked();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int wed_id = mod->index(index.row(), 0).data().toInt();

    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->clear();
    QSqlTableModel *events = new QSqlTableModel();
    events->setTable("Events");
    events->select();
    for (int i = 0; i < events->rowCount(); ++i)
    {
        if (events->record(i).value(6).toInt() == wed_id)
        {
            QString name = events->record(i).value(1).toString();
            QString description = events->record(i).value(2).toString();
            QTime time = QTime::fromString(events->record(i).value(3).toString(), "hh:mm:ss");
            int price = events->record(i).value(4).toInt();
            QPixmap pic = QPixmap(events->record(i).value(5).toString());
            ui->tabWidget->addTab(new QWidget(), name);
        }
    }
    ui->tabWidget->addTab(new QWidget(), "+");
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
