#include "asteroidbelt.h"

#include <QTime>

AsteroidBelt::AsteroidBelt()
{
    centerX = centerY = 0.0;
    radiusMin, radiusMax = 0;
    asteroidNumber = 0;
    surfaceColor = QColor("white");

    speed_range_from = -5;
    speed_range_to = 5;

    rotation = 0.0;
}

AsteroidBelt::AsteroidBelt(qreal centerX,
                           qreal centerY,
                           qint32 radiusMin,
                           qint32 radiusMax,
                           qint32 number,
                           QColor surfaceColor,
                           qreal rotation = 0.0) : AsteroidBelt()
{
    qsrand(QTime::currentTime().msec());
    this->centerX = centerX;
    this->centerY = centerY;
    this->radiusMin = radiusMin;
    this->radiusMax = radiusMax;
    this->asteroidNumber = number;
    this->surfaceColor = surfaceColor;
    this->rotation = rotation;

    qDebug() << QString("Center: (%1,%2), %3<radius<%4, %5, %6<speed<%7, %8")
                .arg(centerX)
                .arg(centerY)
                .arg(radiusMin)
                .arg(radiusMax)
                .arg(number)
                .arg(speed_range_from)
                .arg(speed_range_to)
                .arg(rotation);
}

void AsteroidBelt::generate(QGraphicsScene *scene)
{
    for (int i = 0; i < asteroidNumber; ++i){
        qreal angle = qrand() % 360;
        qint32 radius = qrand() % (radiusMax-radiusMin) + radiusMin;
        qreal x = centerX + radius * sin(angle);
        qreal y = centerY + radius * cos(angle);

        qreal dx = centerX - x;
        qreal dy = centerY - y;

        qreal rotation_x = -dy / hypot(dx,dy) * rotation;
        qreal rotation_y = dx / hypot(dx,dy) * rotation;

        FlyObject* obj = new FlyObject(QString("Asteroid %1").arg(i), 100, x, y,
                                       qrand() % (speed_range_to-speed_range_from) + speed_range_from + rotation_x,
                                       qrand() % (speed_range_to-speed_range_from) + speed_range_from + rotation_y);

        obj->initSurface(1, surfaceColor);

        scene->addItem(obj);
    }
}
