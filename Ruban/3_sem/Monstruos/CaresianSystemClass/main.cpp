#include <iostream>
#include "cartesiansystem.h"
#include <math.h>

using namespace std;

class NewFunc1 : public UserFunc
{
public:
    NewFunc1() {}
    double func(double x) {
        return x;
    }
};

class NewFunc2 : public UserFunc
{
public:
    NewFunc2() {}
    double func(double x) {
        return x * x;
    }
};

class NewFunc3 : public UserFunc
{
public:
    NewFunc3() {}
    double func(double x) {
        return x * x * x;
    }
};

class NewFunc4 : public UserFunc
{
public:
    NewFunc4() {}
    double func(double x) {
        return x * x * x * x;
    }
};

class NewFunc5 : public UserFunc
{
public:
    NewFunc5() {}
    double func(double x) {
        return x * x * x * x * x;
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
