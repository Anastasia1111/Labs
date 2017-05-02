#ifndef FLYOBJECT_H
#define FLYOBJECT_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>

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

    FlyObject(QString name, qreal x, qreal y, qreal vx, qreal vy, qreal mass, qint32 type);

    ~FlyObject();

    QRectF boundingRect() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void initSurface(qreal R, QColor surfaceColor);

    qreal dist(FlyObject *other);

    void calcAccelTo(FlyObject *other);

    qreal fx(qreal local_x);
    qreal fy(qreal local_y);

    void calcX();
    void calcY();

    void updateXY();

public:
    qreal mass;
    qreal x, y, vx, vy, ax, ay;
    qreal radius;
    QColor surfaceColor;
    QString name;
    QList<FlyObject *> others;

    qint32 type;
};

#endif // FLYOBJECT_H