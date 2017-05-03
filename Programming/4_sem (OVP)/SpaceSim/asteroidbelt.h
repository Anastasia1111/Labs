#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

#include <QTime>

#include "flyobject.h"

class AsteroidBelt
{
public:
    AsteroidBelt();
    AsteroidBelt(qint32 number,
                 qreal centerX,
                 qreal centerY,
                 qint32 radiusMin,
                 qint32 radiusMax,
                 QColor surfaceColor,
                 qreal rotation);

    void generate(QList<FlyObject *> &system);

public:
    qreal centerX, centerY;
    qint32 radiusMin, radiusMax;
    qint32 asteroidNumber;
    QColor surfaceColor;
    qint32 speed_range_from, speed_range_to;
    qreal rotation;
};

#endif // ASTEROIDBELT_H