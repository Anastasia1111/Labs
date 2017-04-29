#ifndef FLYOBJECT_H
#define FLYOBJECT_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>

#define SIM_PRECISION 0.1

class FlyObject : public QGraphicsItem
{
public:
    FlyObject();

    FlyObject(QString name, qreal mass, qreal x, qreal y, qreal vx, qreal vy);

    QRectF boundingRect() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void initSurface(qreal R, QColor surfaceColor);

    qreal getX();
    qreal getY();
    qreal getMass();

    qreal dist(FlyObject *other);

    void calcAccelTo(FlyObject *other);

    qreal fx(qreal local_x);
    qreal fy(qreal local_y);

    void calcX();
    void calcY();

    void updateXY();

private:
    qreal mass;
    qreal x, y, vx, vy, ax, ay;
    qreal radius;
    QColor surfaceColor;
    QString name;
    QList<FlyObject *> others;
};

#endif // FLYOBJECT_H