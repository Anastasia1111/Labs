#ifndef SPACEITEM_H
#define SPACEITEM_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>

class SpaceItem :public QGraphicsItem
{

public:
    SpaceItem(qreal x, qreal y);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    struct vec {
        qreal angle;
        QPointF center;
    }; //spining vector

    vec v;
    qreal mass, radius;

    void doCollision();
};

#endif // SPACEITEM_H