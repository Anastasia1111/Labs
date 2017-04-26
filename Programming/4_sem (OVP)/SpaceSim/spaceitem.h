#ifndef SPACEITEM_H
#define SPACEITEM_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class SpaceItem :public QGraphicsItem
{

public:
    SpaceItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    struct vec {
        qreal angle;
        qreal speed;
    }; //spining vector

    vec v;
    qreal mass, radius;

    void advance(int phase);
    void doCollision();
};

#endif // SPACEITEM_H