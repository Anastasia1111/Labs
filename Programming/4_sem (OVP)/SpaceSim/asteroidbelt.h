#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

#include "flyobject.h"

class AsteroidBelt
{
public:
    AsteroidBelt();
    AsteroidBelt(qreal centerX,
                qreal centerY,
                qint32 radiusMin,
                qint32 radiusMax,
                qint32 number,
                QColor surfaceColor,
                qreal rotation);

    void generate(QGraphicsScene *scene);

public:
    qreal centerX, centerY;
    qint32 radiusMin, radiusMax;
    qint32 asteroidNumber;
    QColor surfaceColor;
    qint32 speed_range_from, speed_range_to;
    qreal rotation;
};

#endif // ASTEROIDBELT_H