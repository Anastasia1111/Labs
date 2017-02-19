#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labelX = new QLabel(this);
    labelY = new QLabel(this);
    statusBar()->addWidget(labelY);
    statusBar()->addWidget(labelX);
    statusBar()->addWidget(sliderPen);

    startTimer(0);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(slotAboutProgram()),
            Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* e)
{
    QPoint p = this->mapFromGlobal(QCursor::pos());
    QRect windowRect = this->rect();

    if(windowRect.contains(p))
    {
        labelX->setText("X=" + QString().setNum(p.x()));
        labelY->setText("Y=" + QString().setNum(windowRect.height() - p.y()));
    }
}

void MainWindow::slotAboutProgram()
{
    QMessageBox::about(this, "About",
                       QString("%1 v. %2")
                       .arg(qApp->applicationName())
                       .arg(qApp->applicationVersion()));
}