#include "mainwindow.h"
#include "ui_mainwindow.h"

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
        for (int i=0; i<ui->listWidget_2->count(); i++) {
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