#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWizard(parent)
{}

MainWindow::~MainWindow()
{}

void MainWindow::showHelp()
{
    /*QLabel *help = new QLabel("Помочь?");
    help->setWindowTitle("Help");
    help->setGeometry(500, 200, 400, 400);
    show();*/
    QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Help?", "Keep calm and relax.");
    msg->show();
}
