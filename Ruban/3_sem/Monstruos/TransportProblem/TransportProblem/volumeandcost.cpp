#include "volumeandcost.h"

VolumeAndCost::VolumeAndCost(int volume, int cost) : v(volume), c(cost)
{

}

int VolumeAndCost::fullCost()
{
    return v*c;
}

int VolumeAndCost::getV() const
{
    return v;
}

void VolumeAndCost::setV(int value)
{
    v = value;
    work = (v == 0 ? false : true);
}

int VolumeAndCost::getC() const
{
    return c;
}

void VolumeAndCost::setC(int value)
{
    c = value;
}

std::istream &operator>>(std::istream &str, VolumeAndCost &inVC)
{
    char buf;
    str >> buf;
    if(buf != '(')
        return str;
    str >> inVC.v >> buf;
    if(buf != '/')
        return str;
    str >> inVC.c >> buf;
    return str;
}

bool VolumeAndCost::isWorking() const
{
    return work;
}

void VolumeAndCost::setWork(bool value)
{
    if(value == false)
        v = 0;
}

std::ostream &operator<<(std::ostream &str, const VolumeAndCost &outVC)
{
    str << "(" << outVC.v << "/" << outVC.c << ")";
    return str;
}

