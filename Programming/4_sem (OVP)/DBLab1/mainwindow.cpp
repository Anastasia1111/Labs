#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase(this);

    /*db->connectToDataBase(":memory:");
    this->setDefaultValues();
    this->setupTables();*/

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
        view[ui->tabWidget->currentIndex()]->sortByColumn(1, Qt::DescendingOrder);
        lastOrder = Qt::DescendingOrder;
    } else {
        view[ui->tabWidget->currentIndex()]->sortByColumn(1, Qt::AscendingOrder);
        lastOrder = Qt::AscendingOrder;
    }
}

void MainWindow::on_lineEdit_CharSearch_textChanged(const QString &arg1)
{
    QTableView* curView = view[ui->tabWidget->currentIndex()];
    curView->setSelectionMode(QAbstractItemView::MultiSelection);
    curView->clearSelection();
    for (int i = 0; i < curView->model()->rowCount(); ++i){
        QString str = curView->model()->index(i,1).data().toString();
        if (str.contains(arg1) == true) curView->selectRow(i);
    }
    if (arg1 == "") curView->clearSelection();
}

void MainWindow::on_lineEdit_WordSearch_textChanged(const QString &arg1)
{
    QTableView* curView = view[ui->tabWidget->currentIndex()];
    curView->setSelectionMode(QAbstractItemView::MultiSelection);
    curView->clearSelection();
    for (int i = 0; i < curView->model()->rowCount(); ++i){
        QString str = curView->model()->index(i,1).data().toString();
        if (str == arg1) curView->selectRow(i);
    }
}

void MainWindow::on_pushButton_AddRecord_clicked()
{
    QSqlRelationalTableModel* curMod = mod[ui->tabWidget->currentIndex()];
    curMod->insertRow(curMod->rowCount());
}

void MainWindow::on_actionAbout_LW_triggered()
{
    QMessageBox::about(this, "About programm",
                       QString("%1 v. %2")
                       .arg(qApp->applicationName())
                       .arg(qApp->applicationVersion()));
}

void MainWindow::setDefaultValues()
{
    QSqlQuery query;
    query.exec("insert into Faculty values(1, 'MTS', '1', '4')");
    query.exec("insert into Faculty values(2, 'IVT', '2', '10')");
    query.exec("insert into Faculty values(3, 'AES', '3', '6')");

    query.exec("insert into Groups values(1, 'R-31', 'Petrov', '17', 1)");
    query.exec("insert into Groups values(2, 'R-32', 'Ivanov', '20', 1)");
    query.exec("insert into Groups values(3, 'R-33', 'Sidorov', '18', 1)");

    query.exec("insert into Students values(1, 'Filippov', 'Nekrasova', '321-31-12', 1)");
    query.exec("insert into Students values(2, 'Mazunin', 'Kirova', '343-32-54', 1)");
    query.exec("insert into Students values(3, 'Fedorinin', 'Vybornaya', '345-32-23', 1)");
}

void MainWindow::setupTables()
{
    view.clear();
    mod.clear();

    QTableView* newView = new QTableView();
    QSqlRelationalTableModel* newMod = new QSqlRelationalTableModel();
    newMod->setTable("Faculty");
    newMod->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    newMod->setHeaderData(1, Qt::Horizontal, QObject::tr("Faculty"));
    newMod->setHeaderData(2, Qt::Horizontal, QObject::tr("Year"));
    newMod->setHeaderData(3, Qt::Horizontal, QObject::tr("Number of groups"));
    newMod->select();
    newMod->setEditStrategy(QSqlTableModel::OnFieldChange);
    newView->setModel(newMod);
    newView->setItemDelegate(new QSqlRelationalDelegate(newView));
    mod.push_back(newMod);
    view.push_back(newView);

    newView = new QTableView();
    newMod = new QSqlRelationalTableModel();
    newMod->setTable("Groups");
    newMod->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    newMod->setHeaderData(1, Qt::Horizontal, QObject::tr("Group_name"));
    newMod->setHeaderData(2, Qt::Horizontal, QObject::tr("Name of elder"));
    newMod->setHeaderData(3, Qt::Horizontal, QObject::tr("Number of students"));
    newMod->setHeaderData(4, Qt::Horizontal, QObject::tr("Faculty ID"));
    newMod->setRelation(4, QSqlRelation("Faculty", "id", "Faculty"));
    newMod->select();
    newMod->setEditStrategy(QSqlTableModel::OnFieldChange);
    newView->setModel(newMod);
    newView->setItemDelegate(new QSqlRelationalDelegate(newView));
    mod.push_back(newMod);
    view.push_back(newView);

    newView = new QTableView();
    newMod = new QSqlRelationalTableModel();
    newMod->setTable("Students");
    newMod->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    newMod->setHeaderData(1, Qt::Horizontal, QObject::tr("Full name"));
    newMod->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    newMod->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone number"));
    newMod->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_GR"));
    newMod->setRelation(4, QSqlRelation("Groups", "id", "Group_name"));
    newMod->select();
    newMod->setEditStrategy(QSqlTableModel::OnFieldChange);
    newView->setModel(newMod);
    newView->setItemDelegate(new QSqlRelationalDelegate(newView));
    mod.push_back(newMod);
    view.push_back(newView);

    ui->tabWidget->clear();
    ui->tabWidget->addTab(view[0], mod[0]->tableName());
    ui->tabWidget->addTab(view[1], mod[1]->tableName());
    ui->tabWidget->addTab(view[2], mod[2]->tableName());
}

void MainWindow::on_actionInsert_SQL_code_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, "SQL",
                                         "Code:", QLineEdit::Normal,
                                         QString(""), &ok);
    if (ok && !text.isEmpty()) {
        db->injectSQL(text);
        this->setupTables();
    }
}

void MainWindow::on_actionNew_triggered()
{
    //Вызвать системный диалог сохранения файла в домашней папке пользователя
    QFileDialog* dial =  new QFileDialog(this, "Create file...",
                                        QDir::homePath(), "Database files (*.db);; All files (*.*)");
    dial->exec();
    QString lFileName = dial->selectedFiles().first();
    //Если пользователь не выбрал имя файла для сохранения...
    if(lFileName.isEmpty())
    {
        return; // ... выйти из метода
    }

    system("rm -f "+lFileName.toUtf8());
    /*QFile file(lFileName);
    file.open(QFile::WriteOnly|QFile::Truncate);*/

    db->connectToDataBase(lFileName);
    //this->setDefaultValues();
    this->setupTables();
}

void MainWindow::on_actionOpen_triggered()
{
    //Вызвать системный диалог открытия файла в домашней папке пользователя
    QString lFileName = QFileDialog::getOpenFileName(this, "Open file...",
                        QDir::homePath(),"Database files (*.db);; All files (*.*)");
    //Если пользователь не выбрал имя файла для сохранения...
    if(lFileName.isEmpty())
    {
        return; // ... выйти из метода
    }

    db->connectToDataBase(lFileName);
    //this->setDefaultValues();
    this->setupTables();
}

void MainWindow::on_pushButton_DeleteRecord_clicked()
{
    QTableView* curView = view[ui->tabWidget->currentIndex()];
    QSqlRelationalTableModel* curMod = mod[ui->tabWidget->currentIndex()];
    curMod->removeRow(curView->currentIndex().row());
    this->setupTables();
}
