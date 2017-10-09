#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow wz;
    wz.setOption(QWizard::HaveHelpButton, true);
    QObject::connect(&wz, SIGNAL(helpRequested()), &wz, SLOT(showHelp()));
    wz.setOption(QWizard::NoBackButtonOnStartPage);
    wz.setOption(QWizard::HaveFinishButtonOnEarlyPages);
    wz.setWindowTitle("Заполняем анкету");
    wz.setPage(FIRST_PAGE, new FirstPage);
    wz.setPage(SECOND_PAGE, new SecondPage);
    wz.setPage(TWO_PAGE, new TwoPage("Файлы с шаблоном 2"));
    wz.setPage(FINAL_PAGE, new FinalPage);
    wz.show();

    return a.exec();
}
