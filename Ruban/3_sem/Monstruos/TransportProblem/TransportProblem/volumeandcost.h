#ifndef VOLUMEANDCOST_H
#define VOLUMEANDCOST_H

#include <cstdio>
#include <fstream>
#include <iomanip>

#define FREE -100000000

class VolumeAndCost
{
public:
    VolumeAndCost(int volume = 0, int cost = 0);
    int fullCost();
    int getV() const;
    void setV(int value);

    int getC() const;
    void setC(int value);

    friend std::istream &operator>>(std::istream &str, VolumeAndCost& inVC);
    friend std::ostream &operator<<(std::ostream &str, const VolumeAndCost& outVC);

    bool isWorking() const;
    void setWork(bool value);

private:
    int v;
    int c;
    bool work;
};

#endif // VOLUMEANDCOST_H
