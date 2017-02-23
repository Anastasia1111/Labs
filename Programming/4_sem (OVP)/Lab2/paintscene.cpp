#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);
    penColor = Qt::black;
    penWidth = 1;
    currentPen = new QPen(penColor);
}

PaintScene::~PaintScene()
{
    delete currentPen;
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() == Qt::LeftButton){
        addEllipse(e->scenePos().x() - penWidth/2,
                   e->scenePos().y() - penWidth/2,
                   penWidth,
                   penWidth,
                   QPen(Qt::NoPen),
                   QBrush(penColor));
    }
    if (e->button() == Qt::RightButton){
        addEllipse(e->scenePos().x() - penWidth/2,
                   e->scenePos().y() - penWidth/2,
                   penWidth,
                   penWidth,
                   QPen(Qt::NoPen),
                   QBrush(Qt::white));
    }
    oldLocation = e->scenePos();
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    //some code
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{

    if (e->buttons() & Qt::LeftButton){
        addLine(oldLocation.x(),
                oldLocation.y(),
                e->scenePos().x(),
                e->scenePos().y(),
                *currentPen);
    }
    if (e->buttons() & Qt::RightButton){
        addLine(oldLocation.x(),
                oldLocation.y(),
                e->scenePos().x(),
                e->scenePos().y(),
                QPen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap));
    }
    oldLocation = e->scenePos();
}

void PaintScene::setPenColor(QColor color)
{
    currentPen->setColor(color);
    penColor = color;
}

void PaintScene::setPenWidth(int width)
{
    currentPen->setWidth(width);
    penWidth = width;
}

QColor PaintScene::getPenColor()
{
    return penColor;
}
