#include "dbwindow.h"
#include "ui_dbwindow.h"

DBWindow::DBWindow(QString login, QSqlDatabase db, QWidget *parent) :
    QMainWindow(parent),
    login(login),
    db(db),
    ui(new Ui::DBWindow)
{
    ui->setupUi(this);
    if (login == "admin") ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    else
    {
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->actionNewUser->setVisible(false);
    }
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mod = new QSqlTableModel();
    mod->setTable(TABLE1);
    mod->setHeaderData(1, Qt::Horizontal, QObject::tr("ФИО"));
    mod->setHeaderData(2, Qt::Horizontal, QObject::tr("Пол"));
    mod->setHeaderData(3, Qt::Horizontal, QObject::tr("Мобильный телефон"));
    mod->setHeaderData(4, Qt::Horizontal, QObject::tr("Дата регистрации абонемента"));
    mod->setHeaderData(5, Qt::Horizontal, QObject::tr("Длительность абонемента"));
    mod->setHeaderData(6, Qt::Horizontal, QObject::tr("Прошлые абонементы"));
    mod->setHeaderData(7, Qt::Horizontal, QObject::tr("Справка"), Qt::DecorationRole);
    mod->setHeaderData(8, Qt::Horizontal, QObject::tr("Длительность справки"));
    mod->select();
    ui->tableView->setModel(mod);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

DBWindow::~DBWindow()
{
    delete ui;
}

void DBWindow::on_actionExit_triggered()
{
    ((QWidget *) this->parent())->show();
    this->close();
}

void DBWindow::on_lineEdit_CharSearch_textChanged(const QString &arg1)
{
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->clearSelection();
    for (int i = 0; i < mod->rowCount(); ++i){
        QString str = mod->index(i,1).data().toString();
        if (str.contains(arg1) == true) ui->tableView->selectRow(i);
    }
    if (arg1 == "")
    {
        ui->tableView->clearSelection();
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    }
}

void DBWindow::on_lineEdit_WordSearch_textChanged(const QString &arg1)
{
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->clearSelection();
    for (int i = 0; i < mod->rowCount(); ++i){
        QString str = mod->index(i,1).data().toString();
        if (str == arg1) ui->tableView->selectRow(i);
    }
    if (arg1 == "")
    {
        ui->tableView->clearSelection();
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    }
}

void DBWindow::on_actionNewUser_triggered()
{
    bool ok;
    QString login = QInputDialog::getText(this, "Новый пользователь (логин)", "Введите логин", QLineEdit::Normal, "", &ok);
    if (!ok || login.isEmpty())
        return;
    QString password = QInputDialog::getText(this, "Новый пользователь (пароль)", "Введите пароль", QLineEdit::Normal, "", &ok);
    if (!ok || password.isEmpty())
        return;
    QString question = QInputDialog::getText(this, "Новый пользователь (вопрос)", "Введите контрольный вопрос", QLineEdit::Normal, "", &ok);
    if (!ok || question.isEmpty())
        return;
    QString answer = QInputDialog::getText(this, "Новый пользователь (ответ)", "Введите ответ на контрольный вопрос", QLineEdit::Normal, "", &ok);
    if (!ok || answer.isEmpty())
        return;
    QSqlQuery* query = new QSqlQuery(db);
    query->exec("INSERT INTO " TABLE2 " VALUES(null,'" + Crypter::cryptString(login) + "', '" + Crypter::cryptString(password) + "', '" + Crypter::cryptString(question) + "', '" + Crypter::cryptString(answer) + "');");
    if (!query->isActive())
        QMessageBox::warning(
                    this,
                    tr("Database Error"),
                    query->lastError().text()
        );
    while (query->next())
    {
        qDebug() << "hm..." << endl;
    }
}

void DBWindow::on_actionChangePassword_triggered()
{
    bool ok;
    QString password = QInputDialog::getText(this, "Новый пароль", "Введите новый пароль", QLineEdit::Normal, "", &ok);
    if (!ok || password.isEmpty())
        return;
    QSqlQuery* query = new QSqlQuery(db);
    query->exec("UPDATE " TABLE2 " SET " TABLE2_PAS " = '" + Crypter::cryptString(password) + "' WHERE " TABLE2_LOG " = '" + Crypter::cryptString(login) + "';");
    if (!query->isActive())
        QMessageBox::warning(
                    this,
                    tr("Database Error"),
                    query->lastError().text()
        );
    while (query->next())
    {
        qDebug() << "hm..." << endl;
    }

}
