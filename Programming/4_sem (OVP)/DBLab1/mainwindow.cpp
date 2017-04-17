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

    db->connectToDataBase(":memory:");
    this->setDefaultValues();
    this->setupTables();

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
    if (ui->actionManualInput->isChecked()){
        curMod->insertRow(curMod->rowCount());
    } else {
        dialogWin = new AddRec(this);
        if (dialogWin->exec() == QDialog::Accepted)
        {
            int curIndex = ui->tabWidget->currentIndex();
            QSqlRelationalTableModel* curMod = mod[curIndex];
            QString rec = "insert into " + curMod->tableName() + " values(" + dialogWin->data() + ")";
            QSqlQuery query;
            query.exec(rec);
            this->setupTables();
            ui->tabWidget->setCurrentIndex(curIndex);
        }
    }
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
    query.exec("insert into Faculty values(null, 'MTS', '1', '4', null)");
    query.exec("insert into Faculty values(null, 'IVT', '2', '10', null)");
    query.exec("insert into Faculty values(null, 'AES', '3', '6', null)");

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
    newMod->setTable(TABLE1);
    newMod->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    newMod->setHeaderData(1, Qt::Horizontal, QObject::tr(TABLE1_FAC));
    newMod->setHeaderData(2, Qt::Horizontal, QObject::tr(TABLE1_YEAR));
    newMod->setHeaderData(3, Qt::Horizontal, QObject::tr(TABLE1_GRNUM));
    newMod->select();
    newMod->setEditStrategy(QSqlTableModel::OnFieldChange);
    newView->setModel(newMod);
    newView->hideColumn(4);
    newView->setItemDelegate(new QSqlRelationalDelegate(newView));
    mod.push_back(newMod);
    view.push_back(newView);

    newView = new QTableView();
    newMod = new QSqlRelationalTableModel();
    newMod->setTable(TABLE2);
    newMod->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    newMod->setHeaderData(1, Qt::Horizontal, QObject::tr(TABLE2_NAME));
    newMod->setHeaderData(2, Qt::Horizontal, QObject::tr(TABLE2_LNAME));
    newMod->setHeaderData(3, Qt::Horizontal, QObject::tr(TABLE2_NUM));
    newMod->setHeaderData(4, Qt::Horizontal, QObject::tr(TABLE2_FAC));
    newMod->setRelation(4, QSqlRelation(TABLE1, "id", TABLE1_FAC));
    newMod->select();
    newMod->setEditStrategy(QSqlTableModel::OnFieldChange);
    newView->setModel(newMod);
    newView->setItemDelegate(new QSqlRelationalDelegate(newView));
    mod.push_back(newMod);
    view.push_back(newView);

    newView = new QTableView();
    newMod = new QSqlRelationalTableModel();
    newMod->setTable(TABLE3);
    newMod->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    newMod->setHeaderData(1, Qt::Horizontal, QObject::tr(TABLE3_FN));
    newMod->setHeaderData(2, Qt::Horizontal, QObject::tr(TABLE3_ADDS));
    newMod->setHeaderData(3, Qt::Horizontal, QObject::tr(TABLE3_PNUM));
    newMod->setHeaderData(4, Qt::Horizontal, QObject::tr(TABLE3_IDGR));
    newMod->setRelation(4, QSqlRelation(TABLE2, "id", TABLE2_NAME));
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
    this->setupTables();
}

void MainWindow::on_pushButton_DeleteRecord_clicked()
{
    int curIndex = ui->tabWidget->currentIndex();
    QTableView* curView = view[curIndex];
    QSqlRelationalTableModel* curMod = mod[curIndex];
    curMod->removeRow(curView->currentIndex().row());
    this->setupTables();
    ui->tabWidget->setCurrentIndex(curIndex);
}

void MainWindow::on_actionExport_triggered()
{
    QSqlRelationalTableModel* curMod = mod[ui->tabWidget->currentIndex()];

    // [Collect model data to QString]
    QString textData;
    int rows = curMod->rowCount();
    int columns = curMod->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
                textData += curMod->data(curMod->index(i,j)).toString();
                textData += ", ";      // for .csv file format
        }
        textData += "\n";             // for new line segmentation
    }

    // [Save to file]
    QFileDialog* dial =  new QFileDialog(this, "Create file...",
                                        QDir::homePath(), "CSV files (*.csv)");
    dial->exec();
    QString lFileName = dial->selectedFiles().first();
    QFile csvFile(lFileName);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}