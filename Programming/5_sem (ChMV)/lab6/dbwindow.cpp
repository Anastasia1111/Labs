#include "dbwindow.h"
#include "ui_dbwindow.h"

DBWindow::DBWindow(QString login, QString password, QSqlDatabase db, QWidget *parent) :
    QMainWindow(parent),
    log(login),
    pass(password),
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
    ui->comboBox->addItem("ФИО");
    mod->setHeaderData(2, Qt::Horizontal, QObject::tr("Пол"));
    ui->comboBox->addItem("Пол");
    mod->setHeaderData(3, Qt::Horizontal, QObject::tr("Мобильный телефон"));
    ui->comboBox->addItem("Мобильный телефон");
    mod->setHeaderData(4, Qt::Horizontal, QObject::tr("Дата регистрации абонемента"));
    ui->comboBox->addItem("Дата регистрации абонемента");
    mod->setHeaderData(5, Qt::Horizontal, QObject::tr("Длительность абонемента"));
    ui->comboBox->addItem("Длительность абонемента");
    mod->setHeaderData(6, Qt::Horizontal, QObject::tr("Прошлые абонементы"));
    ui->comboBox->addItem("Прошлые абонементы");
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
    int index = ui->comboBox->currentIndex() + 1;
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->clearSelection();
    for (int i = 0; i < mod->rowCount(); ++i){
        ui->tableView->showRow(i);
        QString str = mod->index(i,index).data().toString();
        if (!str.startsWith(arg1, Qt::CaseInsensitive)) ui->tableView->hideRow(i);
        else ui->tableView->showRow(i);
    }
    if (arg1 == "")
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void DBWindow::on_actionNewUser_triggered()
{
    bool ok;
    QString login = QInputDialog::getText(this, "Новый пользователь (логин)", "Введите логин", QLineEdit::Normal, "", &ok);
    if (!ok || login.isEmpty())
        return;
    QString password = QInputDialog::getText(this, "Новый пользователь (пароль)", "Введите пароль", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty())
        return;
    QString question = QInputDialog::getText(this, "Новый пользователь (вопрос)", "Введите контрольный вопрос", QLineEdit::Normal, "", &ok);
    if (!ok || question.isEmpty())
        return;
    QString answer = QInputDialog::getText(this, "Новый пользователь (ответ)", "Введите ответ на контрольный вопрос", QLineEdit::Normal, "", &ok);
    if (!ok || answer.isEmpty())
        return;
    QSqlQuery* query = new QSqlQuery(db);
    query->prepare(QString("INSERT INTO " TABLE2 " VALUES(null, '%1', '%2', '%3', '%4');")
                   .arg(Crypter::cryptString(login))
                   .arg(Crypter::cryptString(password))
                   .arg(Crypter::cryptString(question))
                   .arg(Crypter::cryptString(answer))
                   );
    qDebug() << query->lastQuery() << endl;
    query->exec();
    if (!query->isActive())
        QMessageBox::warning(
                    this,
                    tr("Database Error"),
                    query->lastError().text()
        );
    emit newUserAdded();
    while (query->next())
    {
        qDebug() << "hm..." << endl;
    }
}

void DBWindow::on_actionChangePassword_triggered()
{
    bool ok;
    QString oldPassword = QInputDialog::getText(this, "Новый пароль", "Введите старый пароль", QLineEdit::Password, "", &ok);
    if (!ok)
        return;
    if (oldPassword != pass)
    {
        QMessageBox::warning(
                    this,
                    tr("Неверный пароль"),
                    tr("Неверный пароль")
        );
        return;
    }
    while (true)
    {
        QString password1 = QInputDialog::getText(this, "Новый пароль", "Введите новый пароль", QLineEdit::Password, "", &ok);
        if (!ok) return;
        if (password1.isEmpty())
        {
            QMessageBox::warning(
                        this,
                        tr("Неверный пароль"),
                        tr("Пароль не может быть пустым")
            );
            continue;
        }
        QString password2 = QInputDialog::getText(this, "Новый пароль", "Еще раз введите новый пароль", QLineEdit::Password, "", &ok);
        if (!ok) return;
        if (password1 != password2)
        {
            QMessageBox::warning(
                        this,
                        tr("Неверный пароль"),
                        tr("Введенные пароли не совпадают")
            );
            continue;
        }
        pass = password1;
        break;
    }
    QSqlQuery* query = new QSqlQuery(db);
    query->exec("UPDATE " TABLE2 " SET " TABLE2_PAS " = '" + Crypter::cryptString(pass) + "' WHERE " TABLE2_LOG " = '" + Crypter::cryptString(log) + "';");
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
    emit newUserAdded();
}
