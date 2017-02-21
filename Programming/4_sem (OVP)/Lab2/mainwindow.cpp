#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labelXY = new QLabel(this);
    sliderPen = new QSlider(Qt::Horizontal, this);
    sliderPen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    statusBar()->addWidget(labelXY);
    statusBar()->addPermanentWidget(sliderPen);

    renderScene = new QGraphicsScene(this);

    startTimer(0);
}

MainWindow::~MainWindow()
{
    delete labelXY;
    delete sliderPen;
    delete renderScene;
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* e)
{
    QPoint p = this->mapFromGlobal(QCursor::pos());
    QRect windowRect = this->rect();

    if(windowRect.contains(p))
    {
        labelXY->setText("X=" + QString().setNum(p.x()) +
                         " Y=" + QString().setNum(windowRect.height() - p.y()));
    }
}

int MainWindow::on_actionNew_triggered()
{
    if (!ui->picDrawingSurface->scene()) {
        ui->picDrawingSurface->setScene(renderScene);
        return 1;
    } else {
        QMessageBox question(QMessageBox::Question, "Save file?", "Do you want to save image before creating something new?",
                             QMessageBox::Ok, this);
        question.addButton(QMessageBox::No);
        question.addButton(QMessageBox::Cancel);
        question.exec();
        if (question.clickedButton() == question.button(QMessageBox::Ok)){
            on_actionSave_triggered();
            return 1;
        } else {
            if (question.clickedButton() == question.button(QMessageBox::No)){
                renderScene->clear();
                ui->picDrawingSurface->update();
                return 1;
            } else {
                return 0;
            }
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if (on_actionNew_triggered()){ //создаем или очищаем сцену
        //Вызвать системный диалог открытия файла в домашней папке пользователя
        QString lFileName = QFileDialog::getOpenFileName(this, "Open file...",
                            QDir::homePath(),"JPEG Image (*.jpg);; Bitmap Image (*.bmp);;"
                                             "GIF Image (*.gif);; PNG Image (*.png)");
        //указываем фильтры для просмотра файлов
        if (lFileName.isEmpty()) //Если пользователь не выбрал ни одного файла
        {
            return; //выйти из метода
        }

        renderScene->addPixmap(QPixmap(lFileName));
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About programm",
                       QString("%1 v. %2")
                       .arg(qApp->applicationName())
                       .arg(qApp->applicationVersion()));
}

void MainWindow::on_actionColor_triggered()
{

}

void MainWindow::on_actionRedo_triggered()
{

}

void MainWindow::on_actionUndo_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionSave_triggered()
{
    if (!ui->picDrawingSurface->scene()) {
        return; // ... выйти из метода
    }

    //Вызвать системный диалог сохранения файла в домашней папке пользователя
    QString lFileName = QFileDialog::getSaveFileName(this, "Save file...",
                        QDir::homePath(),"JPEG Image (*.jpg);; Bitmap Image (*.bmp);;"
                                         "PNG Image (*.png)");
    //Если пользователь не выбрал имя файла для сохранения...
    if(lFileName.isEmpty())
    {
        return; // ... выйти из метода
    }

    QPixmap image(ui->picDrawingSurface->width(), ui->picDrawingSurface->height());
    QPainter painter(&image);
    renderScene->render(&painter);
    image.save(lFileName);
}