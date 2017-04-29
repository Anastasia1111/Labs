#include "space.h"
#include "ui_space.h"

#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>
#include <QDebug>

Space::Space(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Space)
{
    ui->setupUi(this);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    statusBar()->addWidget(new QLabel("New system: Ctrl+N | Open file: Ctrl+O | Save file: Ctrl+S | Start/Pause: Space | Exit: Ctrl+Q"));

    startTimer(0);
}

Space::~Space()
{
    delete ui;
}

void Space::spaceInit()
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    QPixmap bg(1000, 1000);
    bg.fill(spaceColor);
    QPixmap result(1000, 1000);
    QPainter painter(&result);
    painter.drawPixmap(0, 0, bg);
    painter.setBrush(starColor);
    for (qint32 i = 0; i < stars; ++i){
        painter.drawEllipse(qrand()%1000,qrand()%1000,2,2);
    }
    scene->setBackgroundBrush(result);
    ui->graphicsView->setScene(scene);

    /*AsteroidBelt* belt = new AsteroidBelt(0,0,50,75,150,QColor("red"),5);
    belt->generate(scene);*/
}

FlyObject* Space::join(FlyObject *obj1, FlyObject *obj2)
{
    QString name = obj1->name + " " + obj2->name;
    qreal mass = obj1->mass + obj2->mass;

    qreal x = (obj1->x * obj1->mass + obj2->x * obj2->mass) / mass;
    qreal y = (obj1->y * obj1->mass + obj2->y * obj2->mass) / mass;

    qreal vx = (obj1->vx * obj1->mass + obj2->vx * obj2->mass) / mass;
    qreal vy = (obj1->vy * obj1->mass + obj2->vy * obj2->mass) / mass;

    QColor new_color = obj1->surfaceColor;
    if (obj2->mass >= obj1->mass)
        new_color = obj2->surfaceColor;

    FlyObject *obj3 = new FlyObject(name, mass, x, y, vx, vy);
    qreal radius = pow(mass, 1/3) / 2;
    obj3->initSurface(radius, new_color);

    return obj3;
}

void Space::timerEvent(QTimerEvent* e)
{
    //drawing
}

void Space::closeEvent(QCloseEvent *e)
{
    if (ui->graphicsView->scene()) {
        QMessageBox question(QMessageBox::Question, "Save file?", "Do you want to save system before exit?",
                             QMessageBox::Ok, this);
        question.addButton(QMessageBox::No);
        question.addButton(QMessageBox::Cancel);
        question.exec();
        if (question.clickedButton() == question.button(QMessageBox::Ok)){
            on_actionSave_triggered();
            e->accept();
        } else {
            if (question.clickedButton() == question.button(QMessageBox::Cancel)){
                e->ignore();
            }
        }
    }
}

bool Space::on_actionNew_triggered()
{
    if (!ui->graphicsView->scene()) {
        spaceColor = QColor("black");
        starColor = QColor("white");
        qsrand(QTime::currentTime().msec());
        stars = qrand() % 600 + 150;
        csType = STOP;
        spaceInit();
        return true;
    } else {
        QMessageBox question(QMessageBox::Question, "Save file?", "Do you want to save system before creating something new?",
                             QMessageBox::Ok, this);
        question.addButton(QMessageBox::No);
        question.addButton(QMessageBox::Cancel);
        question.exec();
        if (question.clickedButton() == question.button(QMessageBox::Ok)){
            on_actionSave_triggered();
            return true;
        } else {
            if (question.clickedButton() == question.button(QMessageBox::No)){
                spaceInit();
                return true;
            } else {
                return true;
            }
        }
    }
}

void Space::on_actionSave_triggered()
{
    if (!ui->graphicsView->scene()) {
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save file...",
                        QDir::homePath(),"Configuration files (*.ini);; All files (*.*)");
    if(fileName.isEmpty())
    {
        return;
    }

    //save data
}

void Space::on_actionFile_triggered()
{
    if (on_actionNew_triggered()){
        QString fileName = QFileDialog::getOpenFileName(this, "Open file...",
                            QDir::homePath(),"Configuration files (*.ini);; All files (*.*)");
        if(fileName.isEmpty())
        {
            return;
        }
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.startsWith("SPACE_COLOR:")){
                    spaceColor = QColor(line.section(':',1,1));
                }
                if (line.startsWith("STAR_COLOR:")){
                    starColor = QColor(line.section(':',1,1));
                }
                if (line.startsWith("STAR_NUM:")){
                    stars = line.section(':',1,1).toInt();
                }
                if (line.startsWith("ON_COLLISION:")){
                    csType = line.section(':',1,1).toInt();
                }
            }
            spaceInit();
            file.close();
            qDebug() << "File opened successfully";
        }
        else
        {
            QMessageBox::warning(this, "Error",
                                 QString("Could not open file %1 for reading").arg(file.fileName()),
                                 QMessageBox::Ok);
        }
    }
}

void Space::on_actionSP_triggered()
{
    //start or stop
}