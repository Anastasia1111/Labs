#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

#include <QtAlgorithms>

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
    ~AsteroidBelt();

    void generate(QGraphicsScene *scene);
    void degenerate();

public:
    qreal centerX, centerY;
    qint32 radiusMin, radiusMax;
    qint32 asteroidNumber;
    QColor surfaceColor;
    qint32 speed_range_from, speed_range_to;
    qreal rotation;

    QList<FlyObject *> asteroids;
};

#endif // ASTEROIDBELT_H