#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Database Laboratory Work #1\n(DataBase Management System)");
    a.setApplicationVersion(QString("%1.%2")
                            .arg(MAJOR_VERSION)
                            .arg(MINOR_VERSION));

    MainWindow w;
    w.show();

    return a.exec();
}
