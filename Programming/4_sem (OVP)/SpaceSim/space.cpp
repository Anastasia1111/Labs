#include "space.h"
#include "ui_space.h"

#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

Space::Space(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Space)
{
    ui->setupUi(this);

    //something

    statusBar()->addWidget(new QLabel("New system: Ctrl+N | Open file: Ctrl+O | Save file: Ctrl+S | Start/Pause: Space | Exit: Ctrl+Q"));

    startTimer(0);
}

Space::~Space()
{
    delete ui;
}

void Space::timerEvent(QTimerEvent* e)
{
    qDebug() << "tick";
}

void Space::on_actionFile_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this, "Open file...",
                        QDir::homePath(),"Configuration files (*.ini);; All files (*.*)");
    //Если пользователь не выбрал имя файла для сохранения...
    if(FileName.isEmpty())
    {
        return; // ... выйти из метода
    }
    QFile file(FileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        spaceColor = QColor("black");
        starColor = QColor("white");
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("SPACE_COLOR:")){
                spaceColor = QColor(line.section(':',1,1));
            }
            if (line.startsWith("STAR_COLOR:")){
                starColor = QColor(line.section(':',1,1));
            }
        }
        file.close(); //закрываем открытый файл
    }
    else
    {
        QMessageBox::warning(this, "Error",
                             QString("Could not open file %1 for reading").arg(file.fileName()),
                             QMessageBox::Ok);
    }
}
