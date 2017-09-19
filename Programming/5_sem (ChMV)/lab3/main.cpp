#include "widget.h"
#include <QApplication>
#include <QProgressDialog>
#include <QThread>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QFile style(":style.qss");
    style.open(QFile::ReadOnly);
    QString st = QLatin1String(style.readAll());
    a.setStyleSheet(st);
    QProgressDialog *dial = new QProgressDialog("Подождите...", "&Cancel", 0, 100);
    for(int i = 0; i <= 100; ++i)
    {
        dial->setValue(i);
        a.processEvents();
        if(dial->wasCanceled())
            break;
        ++i;
        QThread::msleep(150);
    }
    return a.exec();
}
