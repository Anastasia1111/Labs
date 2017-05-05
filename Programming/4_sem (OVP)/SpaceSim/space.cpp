#include "space.h"
#include "ui_space.h"

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
    system.clear();
}

void Space::setBG(QGraphicsScene *scene)
{
    if (scene != NULL){
        QPixmap bg(width, height);
        bg.fill(spaceColor);
        QPainter painter(&bg);
        painter.setBrush(starColor);
        for (qint32 i = 0; i < stars; ++i){
            painter.drawEllipse(qrand()%width,qrand()%height,2,2);
        }
        scene->setBackgroundBrush(bg);
    }
}

void Space::spaceInit()
{
    this->setFixedSize(width,height);

    if (ui->graphicsView->scene() != NULL)
        delete ui->graphicsView->scene();

    QGraphicsScene* scene = new QGraphicsScene(this);
    setBG(scene);
    ui->graphicsView->setScene(scene);

    for (qint32 i = 0; i < system.size(); ++i){
        scene->addItem(system.at(i));
    }

    topLeftX = topLeftY = 0;
}

FlyObject* Space::merge(FlyObject *obj1, FlyObject *obj2)
{
    QString name = obj1->name + "+" + obj2->name;
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
    qreal radius = obj1->radius * 1.1;
    if (obj1->radius < obj2->radius)
        radius = obj2->radius * 1.1;
    obj3->initSurface(radius, new_color);

    return obj3;
}

void Space::timerEvent(QTimerEvent* e)
{
    if (!paused && ui->graphicsView->scene()){
        for (qint32 i = 0; i < system.size(); ++i){
            FlyObject *obj1 = system.at(i);
            for (qint32 j = 0; j < system.size(); ++j){
                if (obj1 != system.at(j)){
                    FlyObject *obj2 = system.at(j);
                    qreal dist = obj1->dist(obj2);
                    obj1->calcAccelTo(obj2);

                    if (dist <= 0) {
                        FlyObject *mobj = merge(obj1,obj2);
                        switch(csType){
                        case 1:
                            qDebug() << "Collision detected (merge)";
                            system.append(mobj);
                            ui->graphicsView->scene()->addItem(mobj);
                            system.removeAll(obj1);
                            delete obj1;
                            system.removeAll(obj2);
                            delete obj2;
                            break;
                        case 2:
                            qDebug() << "Collision detected (destroy)";
                            system.removeAll(obj1);
                            delete obj1;
                            system.removeAll(obj2);
                            delete obj2;
                            break;
                        case 3:
                            qDebug() << "Collision detected (stop)";
                            paused = true;
                            break;
                        }
                        break;
                    }
                }
            }
        }

        for (qint32 i = 0; i < system.size(); ++i)
            system.at(i)->updateXY();

        ui->graphicsView->scene()->update();

        saved = false;
    }
    if (ui->graphicsView->scene())
        ui->graphicsView->setSceneRect(topLeftX,topLeftY,width,height);

    QString rsBefore = runningStr->text().remove(runningStr->text().length()-1,1);
    runningStr->setText(runningStr->text().remove(0,runningStr->text().length()-1)+rsBefore);
}

void Space::closeEvent(QCloseEvent *e)
{
    paused = true;

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
    paused = true;

    if (!ui->graphicsView->scene() || saved) {
        spaceColor = QColor("black");
        starColor = QColor("white");
        qsrand(QTime::currentTime().msec());
        stars = qrand() % 50 + 150;
        on_actionMerge_triggered();
        topLeftX = 0;
        topLeftY = 0;
        width = 800;
        height = 600;

        qint32 planetLine = height/2;
        FlyObject *star = new FlyObject("Star",
                                        width/2,
                                        planetLine,
                                        0,
                                        0,
                                        qrand()%1000+4000,
                                        STAR);
        star->initSurface(qrand()%5+10,
                          starColor);
        system.append(star);
        qint32 planetCount = qrand()%4+3;
        for (qint32 i = 1; i <= planetCount; ++i){
            FlyObject *planet = new FlyObject(QString("Planet %1").arg(i),
                                              qrand()%width,
                                              planetLine,
                                              0,
                                              qrand()%10-5,
                                              qrand()%90+10,
                                              PLANET);
            planet->initSurface(qrand()%10,
                              QColor(qrand()%256,
                                     qrand()%256,
                                     qrand()%256)
                              );
            system.append(planet);
        }

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
                on_actionMerge_triggered();
                width = 800;
                height = 600;

                ui->graphicsView->scene()->clear();
                system.clear();

                qint32 planetLine = height/2;
                FlyObject *star = new FlyObject("Star",
                                                width/2,
                                                planetLine,
                                                0,
                                                0,
                                                qrand()%1000+4000,
                                                STAR);
                star->initSurface(qrand()%5+10,
                                  starColor);
                system.append(star);
                qint32 planetCount = qrand()%4+3;
                for (qint32 i = 1; i <= planetCount; ++i){
                    FlyObject *planet = new FlyObject(QString("Planet %1").arg(i),
                                                      qrand()%width,
                                                      planetLine,
                                                      0,
                                                      qrand()%10-5,
                                                      qrand()%90+10,
                                                      PLANET);
                    planet->initSurface(qrand()%10,
                                      QColor(qrand()%256,
                                             qrand()%256,
                                             qrand()%256)
                                      );
                    system.append(planet);
                }

                saved = false;

                spaceInit();
            }
        }
    }
}

bool Space::on_actionSave_triggered()
{
    paused = true;

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
    paused = true;

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
        csType = MERGE;
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
    paused = true;

    WinChange* dlg = new WinChange(this);
    if (dlg->exec() == QDialog::Accepted)
    {
        this->setFixedSize(dlg->width(),dlg->height());
        stars = dlg->stars();
    }
}

void Space::on_actionKey_Up_triggered()
{
    topLeftY -= STEP_SIZE;
}

void Space::on_actionKey_Down_triggered()
{
    topLeftY += STEP_SIZE;
}

void Space::on_actionKey_Left_triggered()
{
    topLeftX -= STEP_SIZE;
}

void Space::on_actionKey_Right_triggered()
{
    topLeftX += STEP_SIZE;
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

void Space::on_actionSpace_color_triggered()
{
    paused = true;

    QColor clr = QColorDialog::getColor(spaceColor,
                                        this,
                                        "Change space color");
    if (clr.isValid()){
        spaceColor = clr;
        setBG(ui->graphicsView->scene());
    }
}

void Space::on_actionStars_color_triggered()
{
    paused = true;

    QColor clr = QColorDialog::getColor(starColor,
                                        this,
                                        "Change stars color");
    if (clr.isValid()){
        starColor = clr;
        setBG(ui->graphicsView->scene());
    }
}