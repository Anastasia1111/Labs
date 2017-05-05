#ifndef FLYOBJECT_H
#define FLYOBJECT_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <cmath>

#define SIM_PRECISION 0.33

enum ObjType{
    PLANET = 1,
    STAR = 2,
    ASTEROID = 3
};

class FlyObject : public QGraphicsItem
{
public:

    FlyObject();

    FlyObject(QString name,
              qreal x,
              qreal y,
              qreal vx,
              qreal vy,
              qreal mass,
              qreal r,
              QColor color,
              qint32 type);

    ~FlyObject();

    QRectF boundingRect() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    qreal dist(FlyObject *other);

    void calcAccelTo(FlyObject *other);

    qreal fx(qreal local_x);
    qreal fy(qreal local_y);

    void calcX();
    void calcY();

    void updateXY();

public:
    qreal x, y, vx, vy, ax, ay;
    qreal mass;
    qreal radius;
    QColor color;
    QString name;

    qint32 type;

private:
    QList<FlyObject *> others;

};

#endif // FLYOBJECT_H
