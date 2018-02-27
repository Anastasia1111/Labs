#include <iostream>
#include "cartesiansystem.h"
#include <math.h>
#include <limits>

using namespace std;

class NewFunc1 : public UserFunc
{
public:
    NewFunc1() {}
    double func(double x) {
        return tan(x*x*x);
    }
};

class NewFunc2 : public UserFunc
{
public:
    NewFunc2() {}
    double func(double x) {
        return 10 - x*x*x*x;
    }
};
class NewFunc3 : public UserFunc
{
public:
    NewFunc3() {}
    double func(double x) {
        return 10 * cos(x*x) - 7.5;
    }
};

int main()
{
    vector <UserFunc *> fns;
    fns.push_back(new NewFunc1);
    CartesianSystem a(fns);
    a.run();
    return 0;
}
