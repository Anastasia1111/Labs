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
    return QRect(0,0,radius*2,radius*2);
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
        if(doCollision()){
            painter->drawEllipse(rect);
        } else {
            delete this;
        }
    }
}

bool SpaceItem::doCollision()
{
    QList<QGraphicsItem *> colList = this->collidingItems();
    for (int i = 0; i < colList.size(); ++i) {
        SpaceItem* item = colList.at(i);
        if (item->mass/this->mass <=2 || item->mass/this->mass >=2)
            set
    }
}