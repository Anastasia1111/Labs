#include "colordialog.h"
#include "ui_colordialog.h"

ColorDialog::ColorDialog(QColor color, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);
    ui->spinBox_Red->setValue(color.red());
    ui->horizontalSlider_Red->setValue(color.red());
    ui->spinBox_Blue->setValue(color.blue());
    ui->horizontalSlider_Blue->setValue(color.blue());
    ui->spinBox_Green->setValue(color.green());
    ui->horizontalSlider_Green->setValue(color.green());

    colorResult = color;
    scene = new QGraphicsScene;

    startTimer(0);
}

ColorDialog::~ColorDialog()
{
    delete scene;
    delete ui;
}

void ColorDialog::timerEvent(QTimerEvent* e)
{
    colorResult = QColor(ui->horizontalSlider_Red->value(),
                         ui->horizontalSlider_Green->value(),
                         ui->horizontalSlider_Blue->value());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    scene->setBackgroundBrush(colorResult);
}

void ColorDialog::on_pushButton_clicked()
{
    QColorDialog* clrDial = new QColorDialog(colorResult, this);
    QColor color(clrDial->getColor());
    ui->spinBox_Red->setValue(color.red());
    ui->horizontalSlider_Red->setValue(color.red());
    ui->spinBox_Blue->setValue(color.blue());
    ui->horizontalSlider_Blue->setValue(color.blue());
    ui->spinBox_Green->setValue(color.green());
    ui->horizontalSlider_Green->setValue(color.green());
}

QColor ColorDialog::getColor()
{
    return colorResult;
}
