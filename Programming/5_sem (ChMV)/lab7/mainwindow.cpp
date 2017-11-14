#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->hide();
    ui->progressBar_2->hide();
    ui->Label2->hide();

    time = new QTimer(this);
    time->setInterval(1000 * 60 * 3);
    time->start();
    connect(time, SIGNAL(timeout()), this, SLOT(temporaryFileSave()));

    fileName = "";
    tmpFileName = "";
}

MainWindow::~MainWindow()
{
    if (!tmpFileName.isEmpty())
    {
        QFile tmpFile(tmpFileName);
        tmpFile.remove();
    }
    delete ui;
}

void MainWindow::on_save_clicked()
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        textStream << ui->textEdit->toPlainText();
        file.close();
        temporaryFileSave();

        ui->update->setEnabled(true);
    } else {
        QString lFileName = QFileDialog::getSaveFileName(0,
                                                        QObject::tr("Save File..."),
                                                        QDir::currentPath(),
                                                        QObject::tr("XML Files(*.xml);;All Files (*.*)"));
        if(!lFileName.isEmpty())
        {
            file.setFileName(lFileName);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream textStream(&file);
            textStream << ui->textEdit->toPlainText();
            file.close();
            fileName = lFileName;
            ui->Label1->setText(fileName);
            if (!tmpFileName.isEmpty())
            {
                QFile tmpFile(tmpFileName);
                tmpFile.remove();
            }
            temporaryFileSave();

            ui->update->setEnabled(true);
        }
    }
}

void MainWindow::on_save_as_clicked()
{
    QString lFileName = QFileDialog::getSaveFileName(0,
                                                    QObject::tr("Save File..."),
                                                    QDir::currentPath(),
                                                    QObject::tr("XML Files(*.xml);;All Files (*.*)"));
    if(!lFileName.isEmpty())
    {
        QFile file(lFileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream textStream(&file);
        textStream << ui->textEdit->toPlainText();
        file.close();
        fileName = lFileName;
        ui->Label1->setText(fileName);
        if (!tmpFileName.isEmpty())
        {
            QFile tmpFile(tmpFileName);
            tmpFile.remove();
        }
        temporaryFileSave();

        ui->update->setEnabled(true);
    }
}

void MainWindow::temporaryFileSave()
{
    qDebug() << "Save";
    ui->progressBar->show();
    ui->Label2->show();

    int speed_index = 5000;

    for (int i = 0; i < 100 * speed_index; ++i)
    {
        ui->progressBar->setValue(i/speed_index);
        ui->Label2->setText("Cохранение...");
    }

    QFile* tmpFile;

    if (fileName.isEmpty())
        tmpFileName = QDir::tempPath() + "/" + qApp->applicationName() + "~";
    else
        tmpFileName = fileName + "~";

    tmpFile = new QFile(tmpFileName);
    tmpFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream textStream(tmpFile);
    textStream << ui->textEdit->toPlainText();
    tmpFile->close();

    ui->progressBar->hide();
    ui->Label2->hide();

    time->start();
}

void MainWindow::on_open_clicked()
{
    QString lFileName = QFileDialog::getOpenFileName(0,
                                                    QObject::tr("Open File..."),
                                                    QDir::currentPath(),
                                                    QObject::tr("XML Files(*.xml);;All Files (*.*)"));
    if(!lFileName.isEmpty())
    {
        QFile file(lFileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream out(&file);
        ui->textEdit->setText(out.readAll());
        file.close();
        fileName = lFileName;
        ui->Label1->setText(fileName);
        if (!tmpFileName.isEmpty())
        {
            QFile tmpFile(tmpFileName);
            tmpFile.remove();
        }
        temporaryFileSave();

        ui->update->setEnabled(true);
    }

    ui->update->setEnabled(true);
}

void MainWindow::on_textEdit_textChanged()
{
    ui->update->setEnabled(false);
}

void MainWindow::on_clear_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_exit_clicked()
{
    QMessageBox question(QMessageBox::Question, "Save file?", "Do you want to save file before exit?",
                             QMessageBox::Ok, this);
    question.addButton(QMessageBox::No);
    question.addButton(QMessageBox::Cancel);
    question.exec();
    if (question.clickedButton() == question.button(QMessageBox::Ok)){
        on_save_clicked();
    } else {
        if (question.clickedButton() == question.button(QMessageBox::Cancel)){
            return;
        }
    }
    this->close();
}

void MainWindow::on_update_clicked()
{
    ui->treeWidget->clear();

    QTreeWidget* treeWidget = ui->treeWidget;
    QProgressBar* bar = ui->progressBar_2;
    QFile file(fileName);

    if (ui->dom->isChecked())
        DomParser(&file, treeWidget, bar);
    if (ui->sax->isChecked())
        SaxParser(&file, treeWidget);

    treeWidget->resizeColumnToContents(0);
    treeWidget->resizeColumnToContents(1);
}
