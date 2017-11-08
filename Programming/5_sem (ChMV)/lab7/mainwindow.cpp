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

    tmpFile = new QTemporaryFile();

    time = new QTimer(this);
    time->setInterval(1000 * 60 * 3);
    time->start();
    connect(time, SIGNAL(timeout()), this, SLOT(temporaryFileSave()));

    fileName = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_save_clicked()
{
    QFile file(ui->Label1->text());
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "AAAAAA";
        QTextStream textStream(&file);
        textStream << ui->textEdit->toPlainText();
        file.close();
    } else {
        qDebug() << "MAMA";
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
    }
}

void MainWindow::temporaryFileSave()
{
    qDebug() << "Autosave";
    if (!fileName.isEmpty())
    {
        ui->progressBar->show();
        for (int i = 0; i < 100; ++i)
            ui->progressBar->setValue(i);

        tmpFile->open();
        QTextStream textStream(tmpFile);
        textStream << ui->textEdit->toPlainText();
        tmpFile->close();

        ui->progressBar->hide();
    }
}
