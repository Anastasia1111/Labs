#include "spaceitem.h"

SpaceItem::SpaceItem(qreal x, qreal y)
{
    // random radius
    radius = qrand() % 30;

    // set the speed
    v.angle = (qrand() % 360);

    int startX = x-radius;
    int startY = y-radius;
    v.center = QPointF(x,y);

    setPos(QPointF(startX, startY));
}

QRectF SpaceItem::boundingRect() const
{
    return QRect(-radius,-radius,radius*2,radius*2);
}

void SpaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    // basic collision detection

    if(scene()->collidingItems(this).isEmpty())
    {
        // no collision
        QPen pen(Qt::green, 5);
        painter->setPen(pen);
    }
    else
    {
        // collision !!!
        QPen pen(Qt::red, 5);
        painter->setPen(pen);

        // set the position
        doCollision();
    }

    painter->drawEllipse(rect);
}

void SpaceItem::doCollision()
{
    // get a new position

    // change the angle with randomness
    if(qrand() % 1)
    {
        v.angle = rotation() + (180 + (qrand() % 10));
    }
    else
    {
        v.angle = rotation() + (180 + (qrand() % -10));
    }

    // check if the new position is in bounds
    QPointF newPoint = mapToParent(-(boundingRect().width()), -(boundingRect().width() + 2));

    if(!scene()->sceneRect().contains((newPoint)))
    {
        // move back in bounds
        newPoint = mapToParent(0,0);
    }
    else
    {
        // set the new position
        setPos(newPoint);
    }
}