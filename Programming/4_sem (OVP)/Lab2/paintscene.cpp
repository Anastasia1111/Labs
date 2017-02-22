#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);
    currentPen = new QPen(Qt::black);
}

PaintScene::~PaintScene()
{
    delete currentPen;
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(e->scenePos().x(),
               e->scenePos().y(),
               1,
               1,
               QPen(Qt::NoPen),
               QBrush(Qt::black));
    // Сохраняем координаты точки нажатия
    oldLocation = e->scenePos();
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    //some code
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    // Отрисовываем линии с использованием предыдущей координаты
    addLine(oldLocation.x(),
            oldLocation.y(),
            e->scenePos().x(),
            e->scenePos().y(),
            *currentPen);
    // Обновляем данные о предыдущей координате
    oldLocation = e->scenePos();
}