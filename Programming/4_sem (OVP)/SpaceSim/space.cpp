#include "space.h"
#include "ui_space.h"

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

    topLeftX = topLeftY = 0;
    width = 250;
    height = 250;
    stars = 0;
    system = QList<FlyObject *>();

    fileName = QDir::currentPath();
    saved = true;

    paused = false;

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    runningStr = new QLabel("                   "
                            "New system: Ctrl+N "
                            "| Open file: Ctrl+O "
                            "| Save file: Ctrl+S "
                            "| Start/Pause: Space "
                            "| Set screen size and star number: Ctrl+F "
                            "| Set collision (Merge, Destruction, Stop): F1, F2, F3 "
                            "| Set color (Space, Stars): F5, F6 "
                            "| Movement: Arrows "
                            "| Exit: Ctrl+Q "
                            "               ");

    statusBar()->addWidget(runningStr);

    this->setFixedSize(width,height);

    startTimer(33);
}

Space::~Space()
{
    delete ui;
    delete runningStr;
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

    for (qint32 i = 0; i < system.size(); ++i){
        scene->addItem(system.at(i));
    }
}

FlyObject* Space::merge(FlyObject *obj1, FlyObject *obj2)
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
    qint32 type = ASTEROID;
    if (obj1->type == STAR || obj2->type == STAR) {
        type = STAR;
    } else {
        if (obj1->type == PLANET || obj2->type == PLANET)
            type = PLANET;
    }

    FlyObject *obj3 = new FlyObject(name, x, y, vx, vy, mass, type);
    qreal radius = pow(mass, 1/3) / 2;
    obj3->initSurface(radius, new_color);

    return obj3;
}

void Space::timerEvent(QTimerEvent* e)
{
    if (!paused){
        for (qint32 i = 0; i < system.size(); ++i){
            FlyObject *obj = system.at(i);
            for (qint32 j = 0; j < system.size(); ++j){
                if (obj != system.at(j)){
                    obj->calcAccelTo(system.at(j));
                }
            }
            obj->updateXY();
            QList<QGraphicsItem *> colList = ui->graphicsView->scene()->collidingItems(obj);
            if(!colList.isEmpty()){
                FlyObject *cobj = dynamic_cast<FlyObject *>(colList.at(0));
                if (cobj){
                    switch(csType){
                    case 1:
                        system.append(merge(obj,cobj));
                        system.removeAll(obj);
                        delete obj;
                        system.removeAll(cobj);
                        delete cobj;
                        --i;
                        //paused = true;
                        break;
                    case 2:
                        system.removeAll(obj);
                        delete obj;
                        system.removeAll(cobj);
                        delete cobj;
                        --i;
                        //paused = true;
                        break;
                    case 3:
                        paused = true;
                        break;
                    }
                }
            }
            ui->graphicsView->scene()->update();
        }
    }
    if (ui->graphicsView->scene())
        ui->graphicsView->setSceneRect(topLeftX,topLeftY,width,height);
    saved = false;

    QString rsBefore = runningStr->text().remove(runningStr->text().length()-1,1);
    runningStr->setText(runningStr->text().remove(0,runningStr->text().length()-1)+rsBefore);
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
        on_actionStop_triggered();
        topLeftX = 0;
        topLeftY = 0;
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
                on_actionStop_triggered();
                width = 800;
                height = 600;

                ui->graphicsView->scene()->clear();
                system.clear();

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
        for (qint32 i = 0; i < system.size(); ++i){
            FlyObject *obj = system.at(i);
            switch(obj->type){
            case STAR:
                data += QString("STAR:%1,%2,%3,%4,%5,%6,%7,%8\n\n")
                        .arg(obj->name)
                        .arg(obj->x)
                        .arg(obj->y)
                        .arg(obj->vx)
                        .arg(obj->vy)
                        .arg(obj->mass)
                        .arg(obj->radius)
                        .arg(obj->surfaceColor.name());
                break;
            case PLANET:
                data += QString("PLANET:%1,%2,%3,%4,%5,%6,%7,%8\n\n")
                        .arg(obj->name)
                        .arg(obj->x)
                        .arg(obj->y)
                        .arg(obj->vx)
                        .arg(obj->vy)
                        .arg(obj->mass)
                        .arg(obj->radius)
                        .arg(obj->surfaceColor.name());
                break;
            case ASTEROID:
                data += QString("ASTEROID:%1,%2,%3,%4,%5,%6,%7,%8\n\n")
                        .arg(obj->name)
                        .arg(obj->x)
                        .arg(obj->y)
                        .arg(obj->vx)
                        .arg(obj->vy)
                        .arg(obj->mass)
                        .arg(obj->radius)
                        .arg(obj->surfaceColor.name());
                break;
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

        topLeftX = 0;
        topLeftY = 0;
        spaceColor = QColor("black");
        starColor = QColor("white");
        qsrand(QTime::currentTime().msec());
        stars = qrand() % 50 + 150;
        csType = STOP;
        width = 800;
        height = 600;

        if(ui->graphicsView->scene()){
            ui->graphicsView->scene()->clear();
            system.clear();
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
                    belt->generate(system);
                    qDebug() << system.size();
                }
                if (line.startsWith("PLANET:")){
                    QString objInfo = line.section(':',1,1);
                    FlyObject *obj = new FlyObject(objInfo.section(',',0,0),
                                                   objInfo.section(',',1,1).toDouble(),
                                                   objInfo.section(',',2,2).toDouble(),
                                                   objInfo.section(',',3,3).toDouble(),
                                                   objInfo.section(',',4,4).toDouble(),
                                                   objInfo.section(',',5,5).toDouble(),
                                                   PLANET);
                    obj->initSurface(objInfo.section(',',6,6).toDouble(),
                                     QColor(objInfo.section(',',7,7)));
                    system.append(obj);
                }
                if (line.startsWith("STAR:")){
                    QString objInfo = line.section(':',1,1);
                    FlyObject *obj = new FlyObject(objInfo.section(',',0,0),
                                                   objInfo.section(',',1,1).toDouble(),
                                                   objInfo.section(',',2,2).toDouble(),
                                                   objInfo.section(',',3,3).toDouble(),
                                                   objInfo.section(',',4,4).toDouble(),
                                                   objInfo.section(',',5,5).toDouble(),
                                                   STAR);
                    obj->initSurface(objInfo.section(',',6,6).toDouble(),
                                     QColor(objInfo.section(',',7,7)));
                    system.append(obj);
                }
                if (line.startsWith("ASTEROID:")){
                    QString objInfo = line.section(':',1,1);
                    FlyObject *obj = new FlyObject(objInfo.section(',',0,0),
                                                   objInfo.section(',',1,1).toDouble(),
                                                   objInfo.section(',',2,2).toDouble(),
                                                   objInfo.section(',',3,3).toDouble(),
                                                   objInfo.section(',',4,4).toDouble(),
                                                   objInfo.section(',',5,5).toDouble(),
                                                   ASTEROID);
                    obj->initSurface(objInfo.section(',',6,6).toDouble(),
                                     QColor(objInfo.section(',',7,7)));
                    system.append(obj);
                }
            }
            switch(csType){
            case DESTR:
                on_actionDestr_triggered();
                break;
            case STOP:
                on_actionStop_triggered();
                break;
            case MERGE:
                on_actionMerge_triggered();
                break;
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
    paused = !paused;
}

void Space::on_actionSize_triggered()
{
    WinChange* dlg = new WinChange(this);
    if (dlg->exec() == QDialog::Accepted)
    {
        this->setFixedSize(dlg->width(),dlg->height());
        stars = dlg->stars();
    }
}

void Space::on_actionKey_Up_triggered()
{
    topLeftY -= KEY_MOVE_PX;
}

void Space::on_actionKey_Down_triggered()
{
    topLeftY += KEY_MOVE_PX;
}

void Space::on_actionKey_Left_triggered()
{
    topLeftX -= KEY_MOVE_PX;
}

void Space::on_actionKey_Right_triggered()
{
    topLeftX += KEY_MOVE_PX;
}

void Space::on_actionDestr_triggered()
{
    csType = DESTR;
    ui->actionDestr->setChecked(true);
    ui->actionMerge->setChecked(false);
    ui->actionStop->setChecked(false);
    qDebug() << "destr";
}

void Space::on_actionStop_triggered()
{
    csType = STOP;
    ui->actionDestr->setChecked(false);
    ui->actionMerge->setChecked(false);
    ui->actionStop->setChecked(true);
    qDebug() << "stop";
}

void Space::on_actionMerge_triggered()
{
    csType = MERGE;
    ui->actionDestr->setChecked(false);
    ui->actionMerge->setChecked(true);
    ui->actionStop->setChecked(false);
    qDebug() << "merge";
}