#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Laboratory Work #2/#3\n(Simple Paint with color selection)");
    a.setApplicationVersion(QString("%1.%2")
                            .arg(MAJOR_VERSION)
                            .arg(MINOR_VERSION));

    MainWindow w;
    w.show();

    return a.exec();
}