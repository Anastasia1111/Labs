#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("urw chancery l"));
    MainWindow w;
    w.show();

    return a.exec();
}
