#ifndef PLANET_H
#define PLANET_H

#include "spaceitem.h"

class Planet : public SpaceItem
{
public:
    Planet();

private:
    SpaceItem* satelliteOf;
};

#endif // PLANET_H