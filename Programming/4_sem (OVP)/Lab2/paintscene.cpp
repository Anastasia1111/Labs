#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);
    penColor = Qt::black;
    penWidth = 1;
    currentPen = new QPen(penColor);
    currentPen->setStyle(Qt::SolidLine);
    currentPen->setCapStyle(Qt::RoundCap);
    History = new QList<QPixmap>();

    QPixmap image(1920, 1080);
    QPainter painter(&image);
    this->render(&painter);
    historyCounter = 0;
    History->append(image);
}

PaintScene::~PaintScene()
{
    delete History;
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
    for(int i = historyCounter + 1; i < History->count() - historyCounter - 1; i++){
        History->removeAt(i);
    }
    QPixmap image(1920, 1080);
    QPainter painter(&image);
    this->render(&painter);
    History->append(image);
    if (historyCounter + 1 < 10) historyCounter++;
    if (History->count() - 1 == 10) History->removeFirst();
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
                QPen(Qt::white, penWidth, Qt::SolidLine, Qt::SquareCap));
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

void PaintScene::setPenStyle(Qt::PenStyle style)
{
    currentPen->setStyle(style);
}

QColor PaintScene::getPenColor()
{
    return penColor;
}

void PaintScene::undo()
{
    if (History->count() != 0 && historyCounter != 0){
        this->addPixmap(History->at(--historyCounter));
    }
}

void PaintScene::redo()
{
    if (historyCounter < History->count() - 1){
        this->addPixmap(History->at(++historyCounter));
    }
}

void PaintScene::clear()
{
    QGraphicsScene::clear();
    QPixmap image(1920, 1080);
    QPainter painter(&image);
    this->render(&painter);
    History->clear();
    historyCounter = 0;
    History->append(image);
}