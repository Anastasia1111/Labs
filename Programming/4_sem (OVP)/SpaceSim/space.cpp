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

    width = 0;
    height = 0;
    stars = 0;
    objects = QList<FlyObject *>();
    belts = QList<AsteroidBelt *>();

    fileName = QDir::currentPath();
    saved = true;

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
    this->setFixedSize(width,height);

    if (ui->graphicsView->scene() != NULL)
        delete ui->graphicsView->scene();

    QGraphicsScene* scene = new QGraphicsScene(this);
    QPixmap bg(width, height);
    bg.fill(spaceColor);
    QPainter painter(&bg);
    painter.setBrush(starColor);
    for (qint32 i = 0; i < stars; ++i){
        painter.drawEllipse(qrand()%width,qrand()%height,2,2);
    }
    scene->setBackgroundBrush(bg);
    ui->graphicsView->setScene(scene);

    for (qint32 i = 0; i < objects.size(); ++i){
        scene->addItem(objects.at(i));
    }
    for (qint32 i = 0; i < belts.size(); ++i){
        belts.at(i)->generate(scene);
    }
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
    bool isStar = false;
    if (obj1->isStar || obj2->isStar)
        isStar = true;

    FlyObject *obj3 = new FlyObject(name, mass, x, y, vx, vy, isStar);
    qreal radius = pow(mass, 1/3) / 2;
    obj3->initSurface(radius, new_color);

    return obj3;
}

void Space::timerEvent(QTimerEvent* e)
{
    //drawing
    saved = false;
}

void Space::closeEvent(QCloseEvent *e)
{
    if (ui->graphicsView->scene() && !saved) {
        QMessageBox question(QMessageBox::Question, "Save file?", "Do you want to save system before exit?",
                             QMessageBox::Ok, this);
        question.addButton(QMessageBox::No);
        question.addButton(QMessageBox::Cancel);
        question.exec();
        if (question.clickedButton() == question.button(QMessageBox::Ok)){
            if(on_actionSave_triggered()){
                e->accept();
            } else {
                e->ignore();
            }
        } else {
            if (question.clickedButton() == question.button(QMessageBox::Cancel)){
                e->ignore();
            }
        }
    }
}

void Space::on_actionNew_triggered()
{
    if (!ui->graphicsView->scene() || saved) {
        spaceColor = QColor("black");
        starColor = QColor("white");
        qsrand(QTime::currentTime().msec());
        stars = qrand() % 50 + 150;
        csType = STOP;
        width = 800;
        height = 600;

        //random system generation

        saved = false;

        spaceInit();
    } else {
        QMessageBox question(QMessageBox::Question, "Save file?", "Do you want to save system before creating something new?",
                             QMessageBox::Ok, this);
        question.addButton(QMessageBox::No);
        question.addButton(QMessageBox::Cancel);
        question.exec();
        if (question.clickedButton() == question.button(QMessageBox::Ok)){
            on_actionSave_triggered();
        } else {
            if (question.clickedButton() == question.button(QMessageBox::No)){
                spaceColor = QColor("black");
                starColor = QColor("white");
                qsrand(QTime::currentTime().msec());
                stars = qrand() % 50 + 150;
                csType = STOP;
                width = 800;
                height = 600;

                ui->graphicsView->scene()->clear();
                objects.clear();
                belts.clear();

                //random system generation

                saved = false;

                spaceInit();
            }
        }
    }
}

bool Space::on_actionSave_triggered()
{
    if (!ui->graphicsView->scene()) {
        return false;
    }

    fileName = QFileDialog::getSaveFileName(this, "Save file...",
                                            fileName,"Configuration files (*.ini);; All files (*.*)");
    if(fileName.isEmpty())
    {
        return false;
    }

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QByteArray data;

        data += QString("WIN_WIDTH:%1\n").arg(width);
        data += QString("WIN_HEIGHT:%1\n").arg(height);
        data += QString("STAR_NUM:%1\n").arg(stars);
        data += QString("STAR_COLOR:%1\n").arg(starColor.name());
        data += QString("SPACE_COLOR:%1\n").arg(spaceColor.name());
        data += QString("ON_COLLISION:%1\n\n").arg(csType);
        for (qint32 i = 0; i < belts.size(); ++i){
            AsteroidBelt *belt = belts.at(i);
            data += QString("ASTEROID_BELT:%1,%2,%3,%4,%5,%6,%7\n\n")
                    .arg(belt->asteroidNumber)
                    .arg(belt->centerX)
                    .arg(belt->centerY)
                    .arg(belt->radiusMin)
                    .arg(belt->radiusMax)
                    .arg(belt->surfaceColor.name())
                    .arg(belt->rotation);
        }
        for (qint32 i = 0; i < objects.size(); ++i){
            FlyObject *obj = objects.at(i);
            if (obj->isStar){
                data += QString("STAR:%1,%2,%3,%4,%5,%6,%7,%8\n\n")
                        .arg(obj->name)
                        .arg(obj->x)
                        .arg(obj->y)
                        .arg(obj->vx)
                        .arg(obj->vy)
                        .arg(obj->mass)
                        .arg(obj->radius)
                        .arg(obj->surfaceColor.name());
            } else {
                data += QString("PLANET:%1,%2,%3,%4,%5,%6,%7,%8\n\n")
                        .arg(obj->name)
                        .arg(obj->x)
                        .arg(obj->y)
                        .arg(obj->vx)
                        .arg(obj->vy)
                        .arg(obj->mass)
                        .arg(obj->radius)
                        .arg(obj->surfaceColor.name());
            }
        }

        file.write(data);
        file.close();

        saved = true;
    }
    else
    {
        QMessageBox::warning(this, "Error",
                             QString("Could not open file %1 for writing").arg(file.fileName()),
                             QMessageBox::Ok);

        saved = false;
    }

    return saved;
}

void Space::on_actionFile_triggered()
{
    bool flag;
    if (!ui->graphicsView->scene() || saved) {
        flag = true;
    } else {
        QMessageBox question(QMessageBox::Question, "Save file?", "Do you want to save system before creating something new?",
                             QMessageBox::Ok, this);
        question.addButton(QMessageBox::No);
        question.addButton(QMessageBox::Cancel);
        question.exec();
        if (question.clickedButton() == question.button(QMessageBox::Ok)){
            flag = on_actionSave_triggered();
        } else {
            if (question.clickedButton() == question.button(QMessageBox::No)){
                flag = true;
            } else {
                flag = false;
            }
        }
    }
    if (flag){
        fileName = QFileDialog::getOpenFileName(this, "Open file...",
                                                fileName,"Configuration files (*.ini);; All files (*.*)");
        if(fileName.isEmpty())
        {
            return;
        }

        spaceColor = QColor("black");
        starColor = QColor("white");
        qsrand(QTime::currentTime().msec());
        stars = qrand() % 50 + 150;
        csType = STOP;
        width = 800;
        height = 600;

        if(ui->graphicsView->scene()){
            ui->graphicsView->scene()->clear();
            objects.clear();
            belts.clear();
        }

        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.startsWith("WIN_WIDTH:")){
                    width = line.section(':',1,1).toInt();
                }
                if (line.startsWith("WIN_HEIGHT:")){
                    height = line.section(':',1,1).toInt();
                }
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
                if (line.startsWith("ASTEROID_BELT:")){
                    QString beltInfo = line.section(':',1,1);
                    AsteroidBelt *belt = new AsteroidBelt(beltInfo.section(',',0,0).toDouble(),
                                                          beltInfo.section(',',1,1).toDouble(),
                                                          beltInfo.section(',',2,2).toInt(),
                                                          beltInfo.section(',',3,3).toInt(),
                                                          beltInfo.section(',',4,4).toInt(),
                                                          QColor(beltInfo.section(',',5,5)),
                                                          beltInfo.section(',',6,6).toDouble());
                    belts.append(belt);
                }
                if (line.startsWith("PLANET:")){
                    QString objInfo = line.section(':',1,1);
                    FlyObject *obj = new FlyObject(objInfo.section(',',0,0),
                                                   objInfo.section(',',1,1).toDouble(),
                                                   objInfo.section(',',2,2).toDouble(),
                                                   objInfo.section(',',3,3).toDouble(),
                                                   objInfo.section(',',4,4).toDouble(),
                                                   objInfo.section(',',5,5).toDouble(),
                                                   false);
                    obj->initSurface(objInfo.section(',',6,6).toDouble(),
                                     QColor(objInfo.section(',',7,7)));
                    objects.append(obj);
                }
                if (line.startsWith("STAR:")){
                    QString objInfo = line.section(':',1,1);
                    FlyObject *obj = new FlyObject(objInfo.section(',',0,0),
                                                   objInfo.section(',',1,1).toDouble(),
                                                   objInfo.section(',',2,2).toDouble(),
                                                   objInfo.section(',',3,3).toDouble(),
                                                   objInfo.section(',',4,4).toDouble(),
                                                   objInfo.section(',',5,5).toDouble(),
                                                   true);
                    obj->initSurface(objInfo.section(',',6,6).toDouble(),
                                     QColor(objInfo.section(',',7,7)));
                    objects.append(obj);
                }
            }
            qDebug() << "File opened successfully";
            spaceInit();
            file.close();

            saved = true;
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