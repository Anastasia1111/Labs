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
}

ColorDialog::~ColorDialog()
{
    delete ui;
}

void ColorDialog::timerEvent(QTimerEvent* e)
{
    QGraphicsScene *scene = new QGraphicsScene;
    colorResult = QColor(ui->horizontalSlider_Red->value(),
                         ui->horizontalSlider_Green->value(),
                         ui->horizontalSlider_Blue->value());
    scene->setBackgroundBrush(colorResult);
    ui->graphicsView->setScene(scene);
    delete scene;
}

void ColorDialog::on_pushButton_clicked()
{
    QColor color(QColorDialog().getColor(colorResult,this,"Select Color"));
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