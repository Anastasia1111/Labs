#include "planet.h"
#include <QGraphicsRotation>

Planet::Planet(qreal x, qreal y, SpaceItem *parent):
    SpaceItem(x,y),
    satelliteOf(parent)
{
    v.angle = -0.25;
    radius = 5;
    v.center = QPointF(parent->scenePos().x(), parent->scenePos().y());
    qDebug() << v.center;
}

void Planet::advance(int phase)
{
    if(!phase) return;

    QRectF rect = this->sceneBoundingRect();
    qreal x = rect.x()+radius,
            x0 = v.center.x(),
            y = rect.y()+radius,
            y0 = v.center.x(),
            a = v.angle;
    qreal nx = x0 + (x - x0) * cos(a) - (y - y0) * sin(a);
    qreal ny = y0 + (y - y0) * cos(a) + (x - x0) * sin(a);

    setPos(nx,ny);
}