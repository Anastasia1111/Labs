#include "space.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Space w;
    w.show();

    return a.exec();
}
