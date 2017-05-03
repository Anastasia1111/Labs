#include "flyobject.h"

FlyObject::FlyObject()
{
    mass = 0.0;
    x = y = vx = vy = ax = ay = 0.0;
    radius = 0.0;
    surfaceColor = QColor("black");
    others = QList<FlyObject *>();
    name = "";

    qDebug() << "constructed:" << name << ", (" << x << ", " << y << ") v = (" << vx << ", " << vy << "), mass = " << mass;
}

FlyObject::FlyObject(QString name, qreal x, qreal y, qreal vx, qreal vy, qreal mass, qint32 type)
{
    this->mass = mass;
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->name = name;
    this->type = type;
    others = QList<FlyObject *>();

    qDebug() << "constructed:" << name << ", (" << x << ", " << y << ") v = (" << vx << ", " << vy << "), mass = " << mass;
}

FlyObject::~FlyObject()
{
    others.clear();
    qDebug() << "destroyed:" << name << ", (" << x << ", " << y << ") v = (" << vx << ", " << vy << "), mass = " << mass;
}

QRectF FlyObject::boundingRect() const
{
    return QRect(0,0,radius*2,radius*2);
}

void FlyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    this->setPos(x-radius,y-radius);

    QRectF rect = boundingRect();

    QPen pen(surfaceColor, 1);
    QBrush brush(surfaceColor);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(rect);
}

void FlyObject::initSurface(qreal R, QColor surfaceColor)
{
    this->radius = R;
    this->surfaceColor = surfaceColor;
}

void FlyObject::calcAccelTo(FlyObject *other)
{
    others.append(other);
}

qreal FlyObject::fx(qreal local_x)
{
    qreal a = 0;
    for (int i = 0; i < others.size(); ++i) {
        qreal x = others.at(i)->x;
        qreal y = others.at(i)->y;
        qreal mass = others.at(i)->mass;
        qreal r = std::hypot(x - local_x, y - this->y);
        a += mass * (x - local_x) / (r*r*r);
    }
    return a;
}

qreal FlyObject::fy(qreal local_y)
{
    qreal a = 0;
    for (int i = 0; i < others.size(); ++i) {
        qreal x = others.at(i)->x;
        qreal y = others.at(i)->y;
        qreal mass = others.at(i)->mass;
        qreal r = std::hypot(x - this->x, y - local_y);
        a += mass * (y - local_y) / (r*r*r);
    }
    return a;
}

void FlyObject::calcX()
{
    qreal k1 = SIM_PRECISION * fx(x);
    qreal q1 = SIM_PRECISION * vx;

    qreal k2 = SIM_PRECISION * fx(x + q1 / 2);
    qreal q2 = SIM_PRECISION * (vx + k1 / 2);

    qreal k3 = SIM_PRECISION * fx(x + q2 / 2);
    qreal q3 = SIM_PRECISION * (vx + k2 / 2);

    qreal k4 = SIM_PRECISION * fx(x + q3);
    qreal q4 = SIM_PRECISION * (vx + k3);

    vx += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    x += (q1 + 2 * q2 + 2 * q3 + q4) / 6;
}

void FlyObject::calcY()
{
    qreal k1 = SIM_PRECISION * fy(y);
    qreal q1 = SIM_PRECISION * vy;

    qreal k2 = SIM_PRECISION * fy(y + q1 / 2);
    qreal q2 = SIM_PRECISION * (vy + k1 / 2);

    qreal k3 = SIM_PRECISION * fy(y + q2 / 2);
    qreal q3 = SIM_PRECISION * (vy + k2 / 2);

    qreal k4 = SIM_PRECISION * fy(y + q3);
    qreal q4 = SIM_PRECISION * (vy + k3);

    vy += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    y += (q1 + 2 * q2 + 2 * q3 + q4) / 6;
}

void FlyObject::updateXY()
{
    calcX();
    calcY();
    others.clear();

    qDebug() << "update:" << name << ", (" << x << ", " << y << ") v = (" << vx << ", " << vy << "), mass = " << mass;
}

qreal FlyObject::dist(FlyObject *other)
{
    return std::hypot((x - other->x),(y - other->y));
}
