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
    ui->Label2->hide();

    tmpFile = NULL;

    time = new QTimer(this);
    time->setInterval(1000 * 60 * 3);
    time->start();
    connect(time, SIGNAL(timeout()), this, SLOT(temporaryFileSave()));

    fileName = "";
}

MainWindow::~MainWindow()
{
    if (tmpFile != NULL)
    {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QTextStream out(tmpFile);
            QString tmp = out.readAll();
            qDebug() << tmp;
            in << tmp;
            file.close();
        }

        tmpFile->remove();
    }
    delete ui;
}

void MainWindow::on_save_clicked()
{
    QFile file(ui->Label1->text());
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        textStream << ui->textEdit->toPlainText();
        file.close();
        temporaryFileSave();
    } else {
        fileName = QFileDialog::getSaveFileName(0,
                                                QObject::tr("Save File..."),
                                                QDir::currentPath(),
                                                QObject::tr("XML Files(*.xml);;All Files (*.*)"));
        if(!fileName.isEmpty())
        {
            file.setFileName(fileName);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream textStream(&file);
            textStream << ui->textEdit->toPlainText();
            file.close();
            ui->Label1->setText(fileName);
            if (tmpFile != NULL)
            {
                tmpFile->close();
                tmpFile = NULL;
            }
            temporaryFileSave();
        }
    }
}

void MainWindow::on_save_as_clicked()
{
    fileName = QFileDialog::getSaveFileName(0,
                                            QObject::tr("Save File..."),
                                            QDir::currentPath(),
                                            QObject::tr("XML Files(*.xml);;All Files (*.*)"));
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream textStream(&file);
        textStream << ui->textEdit->toPlainText();
        file.close();
        ui->Label1->setText(fileName);
        if (tmpFile != NULL)
        {
            tmpFile->close();
            tmpFile = NULL;
        }
        temporaryFileSave();
    }
}

void MainWindow::temporaryFileSave()
{
    qDebug() << "Save";
    ui->progressBar->show();
    ui->Label2->show();
    for (int i = 0; i < 500000; ++i)
    {
        ui->progressBar->setValue(i/5000);
        ui->Label2->setText("Cохранение...");
    }

    if (fileName.isEmpty())
    {
        if (tmpFile == NULL)
            tmpFile = new QTemporaryFile();

        tmpFile->close();
        ((QTemporaryFile*)tmpFile)->open();
        QTextStream textStream(tmpFile);
        textStream << ui->textEdit->toPlainText();
    } else {
        if (tmpFile == NULL)
            tmpFile = new QFile(fileName + "~");

        tmpFile->close();
        tmpFile->open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream textStream(tmpFile);
        textStream << ui->textEdit->toPlainText();
    }

    ui->progressBar->hide();
    ui->Label2->hide();

    time->start();
}
