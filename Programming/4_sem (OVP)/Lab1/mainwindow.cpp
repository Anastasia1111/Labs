#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addrec.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_open, SIGNAL(triggered()), this, SLOT(slotOpen()),
            Qt::UniqueConnection);
    connect(ui->action_save, SIGNAL(triggered()), this, SLOT(slotSave()),
            Qt::UniqueConnection);
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()),
            Qt::UniqueConnection);
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(slotAboutProgram()),
            Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpen()
{
    //Вызвать системный диалог открытия файла в домашней папке пользователя
    QString lFileName = QFileDialog::getOpenFileName(this, "Open file...",
                        QDir::homePath(),"Text files (*.txt);; All files (*.*)");
    //указываем фильтры для просмотра файлов
    if (lFileName.isEmpty()) //Если пользователь не выбрал ни одного файла
    {
        return; //выйти из метода
    }
    QFile lFile(lFileName); //Устанавливаем имя открытого файла
    //Если текстовый файл открыт только для чтения...
    if (lFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //читаем все содержимое
        ui->plainTextEdit->setPlainText(lFile.readAll());
        lFile.close(); //закрываем открытый файл
    }
    else
    {
        //Если при открытии файла возникла ошибка выводим диалоговое окно с сообщением,
        //содержащим имя файла, одну кнопку «Ок» и заголовок «Error»
        QMessageBox::warning(this, "Error",
                             QString("Could not open file %1 for reading").arg(lFile.fileName()),
                             QMessageBox::Ok);
    }
}

//Слот для сохранения изменений в текущем файле
void MainWindow::slotSave()
{
    //Вызвать системный диалог сохранения файла в домашней папке пользователя
    QString lFileName = QFileDialog::getSaveFileName(this, "Save file...",
                        QDir::homePath(),"Text files (*.txt);; All files (*.*)");
    //Если пользователь не выбрал имя файла для сохранения...
    if(lFileName.isEmpty())
    {
        return; // ... выйти из метода
    }
    QFile lFile(lFileName); //Устанавливаем имя открытого файла
    //Если текстовый файл открыт для записи
    if (lFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //Создаем временный QByteArray для записи данных
        QByteArray lData;
        //Читаем текст и добавляем QByteArray, записываем в файл
        //и закрываем файл после записи
        for (int i=0; i < ui->listWidget_2->count(); i++) {
            lData.append(ui->listWidget_2->item(i)->text());
        }

        lFile.write(lData);
        lFile.close();
    }
    else
    {
        //Если при открытии файла возникла ошибка выводим диалоговое окно с сообщением,
        //содержащим имя файла, одну кнопку «Ок» и заголовок «Error»
        QMessageBox::warning(this, "Error",
                             QString("Could not open file %1 for writing").arg(lFile.fileName()),
                             QMessageBox::Ok);
    }
}

//Слот для отображения информации о программе
void MainWindow::slotAboutProgram()
{
    //Выводим диалоговое информационное окно с сообщением, куда подставляем версию и название
    //программы возвращаемых QApplication. Указываем — окно содержит заголовок «About».
    QMessageBox::about(this, "About",
                       QString("%1 v. %2")
                       .arg(qApp->applicationName())
                       .arg(qApp->applicationVersion()));
}

void MainWindow::on_pushButton_Start_clicked()
{
    ui->listWidget_1->clear();
    ui->listWidget_2->clear();

    QStringList Strings = ui->plainTextEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts);
    foreach (QString s, Strings)
    {
        QString Str = s.trimmed();
        if (Str.isEmpty()) continue;
        if (ui->radioButton_All->isChecked()) ui->listWidget_1->addItem(Str);
        if (ui->radioButton_Digits->isChecked())
        {
            if (Str.contains(QRegExp("\\d"))) ui->listWidget_1->addItem(Str);
        }
        if (ui->radioButton_Email->isChecked())
        {
            if (Str.contains(QRegExp("\\w+@\\w+\\.\\w+"))) ui->listWidget_1->addItem(Str);
        }
    }
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_1->clear();
    ui->listWidget_2->clear();
    ui->plainTextEdit->clear();
    ui->lineEdit->clear();
    ui->radioButton_All->setChecked(true);
    ui->checkBox_section1->setChecked(true);
}

void MainWindow::on_pushButton_Search_clicked()
{
    QString key = ui->lineEdit->text();

    ui->listWidget->clear();

    QString Str;

    if (ui->checkBox_section1->isChecked())
    {
        for (int i=0; i < ui->listWidget_1->count(); i++) {
            Str = QString(ui->listWidget_1->item(i)->text());
            if (Str.contains(key)) ui->listWidget->addItem(Str);
        }
    }
    if (ui->checkBox_section2->isChecked())
    {
        for (int i=0; i < ui->listWidget_2->count(); i++) {
            Str = QString(ui->listWidget_2->item(i)->text());
            if (Str.contains(key)) ui->listWidget->addItem(Str);
        }
    }
}

void MainWindow::on_pushButton_add_clicked()
{
    dialogWin = new AddRec(this);
    if (dialogWin->exec() == QDialog::Accepted)
    {
        if (dialogWin->isFirstSectionSelected())
        {
            ui->listWidget_1->addItem(dialogWin->text());
        } else {
            ui->listWidget_2->addItem(dialogWin->text());
        }
    }
}

void MainWindow::on_pushButton_del_clicked()
{
    qDeleteAll(ui->listWidget_1->selectedItems());
    qDeleteAll(ui->listWidget_2->selectedItems());
}

void MainWindow::on_pushButton_1_clicked()
{
    foreach (QListWidgetItem* item, ui->listWidget_1->selectedItems())
    {
        ui->listWidget_2->insertItem(ui->listWidget_2->count(), ui->listWidget_1->takeItem(ui->listWidget_1->currentRow()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    foreach (QListWidgetItem* item, ui->listWidget_2->selectedItems())
    {
        ui->listWidget_1->insertItem(ui->listWidget_1->count(), ui->listWidget_2->takeItem(ui->listWidget_2->currentRow()));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int listSize = ui->listWidget_1->count();
    for (int i=0; i < listSize; i++) {
        ui->listWidget_1->setCurrentRow(0);
        ui->listWidget_2->insertItem(ui->listWidget_2->count(), ui->listWidget_1->takeItem(ui->listWidget_1->currentRow()));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int listSize = ui->listWidget_2->count();
    for (int i=0; i < listSize; i++) {
        ui->listWidget_2->setCurrentRow(0);
        ui->listWidget_1->insertItem(ui->listWidget_1->count(), ui->listWidget_2->takeItem(ui->listWidget_2->currentRow()));
    }
}

void MainWindow::on_pushButton_sort1_clicked()
{
    switch(ui->comboBox_1->currentIndex())
    {
    case 0:
        ui->listWidget_1->sortItems(Qt::AscendingOrder);
        break;

    case 1:
        ui->listWidget_1->sortItems(Qt::DescendingOrder);
        break;

    case 2:
        sortItemsByLength(Qt::AscendingOrder, ui->listWidget_1);
        break;

    case 3:
        sortItemsByLength(Qt::DescendingOrder, ui->listWidget_1);
        break;
    }
}
void MainWindow::on_pushButton_sort2_clicked()
{
    switch(ui->comboBox_2->currentIndex())
    {
    case 0:
        ui->listWidget_2->sortItems(Qt::AscendingOrder);
        break;

    case 1:
        ui->listWidget_2->sortItems(Qt::DescendingOrder);
        break;

    case 2:
        sortItemsByLength(Qt::AscendingOrder, ui->listWidget_2);
        break;

    case 3:
        sortItemsByLength(Qt::DescendingOrder, ui->listWidget_2);
        break;
    }
}

bool comparator (const QString& first, const QString& second)
{
    return (first.length() < second.length());
}

bool reverse_comparator (const QString& first, const QString& second)
{
    return (first.length() > second.length());
}

void MainWindow::sortItemsByLength(Qt::SortOrder order, QListWidget *list)
{
    QStringList Strings;
    for (int i=0; i < list->count(); i++) {
        Strings.append(list->item(i)->text());
    }
    std::list<QString> stdStrings = Strings.toStdList();
    if(order == Qt::AscendingOrder)
    {
        stdStrings.sort(comparator);
    } else {
        stdStrings.sort(reverse_comparator);
    }
    Strings = QStringList::fromStdList(stdStrings);
    list->clear();
    list->addItems(Strings);
}
