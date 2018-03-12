#ifndef FRACMATRIXSYMPLEX_H
#define FRACMATRIXSYMPLEX_H

#include "../FracClass/frac.h"
#include <vector>
#include <iostream>

using namespace std;


class FracMatrixSymplex
{
public:
    FracMatrixSymplex();
    void rowMulti(int row, Frac mult);

private:
    Frac **m;
    int xsize;
    int ysize;

};

#endif // FRACMATRIXSYMPLEX_H
