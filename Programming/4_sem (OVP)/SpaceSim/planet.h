#ifndef PLANET_H
#define PLANET_H

#include "spaceitem.h"

class Planet : public SpaceItem
{
public:
    Planet(qreal x, qreal y, SpaceItem* parent);

protected:
    void advance(int phase);

private:
    SpaceItem* satelliteOf;
};

#endif // PLANET_H