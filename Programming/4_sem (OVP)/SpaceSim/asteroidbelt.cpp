#include "asteroidbelt.h"

AsteroidBelt::AsteroidBelt()
{
    centerX = centerY = 0.0;
    radiusMin, radiusMax = 0;
    asteroidNumber = 0;
    color = QColor("white");

    speed_range_from = -5;
    speed_range_to = 5;

    rotation = 0.0;
}

AsteroidBelt::AsteroidBelt(qint32 number,
                           qreal centerX,
                           qreal centerY,
                           qint32 radiusMin,
                           qint32 radiusMax,
                           QColor surfaceColor,
                           qreal rotation = 0.0) : AsteroidBelt()
{
    qsrand(QTime::currentTime().msec());
    this->centerX = centerX;
    this->centerY = centerY;
    this->radiusMin = radiusMin;
    this->radiusMax = radiusMax;
    this->asteroidNumber = number;
    this->color = surfaceColor;
    this->rotation = rotation;
}

void AsteroidBelt::generate(QList<FlyObject *> &system)
{
    for (int i = 0; i < asteroidNumber; ++i){
        qint32 angle = qrand() % 360;
        qint32 radius = qrand() % (radiusMax-radiusMin) + radiusMin;
        qreal x = centerX + radius * sin(angle);
        qreal y = centerY + radius * cos(angle);

        qreal dx = centerX - x;
        qreal dy = centerY - y;

        qreal rotation_x = -dy / std::hypot(dx,dy) * rotation;
        qreal rotation_y = dx / std::hypot(dx,dy) * rotation;

        FlyObject* obj = new FlyObject(QString("Asteroid %1").arg(i),
                                       x,
                                       y,
                                       qrand() % (speed_range_to-speed_range_from) + speed_range_from + rotation_x,
                                       qrand() % (speed_range_to-speed_range_from) + speed_range_from + rotation_y,
                                       qrand() % 5 + 1,
                                       2,
                                       color,
                                       ASTEROID);
        system.append(obj);
    }
}
