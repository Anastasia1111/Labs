#include "fracmatrixsymplex.h"

using namespace std;

FracMatrixSymplex::FracMatrixSymplex()
{

}

void FracMatrixSymplex::rowMulti(int row, Frac mult)
{
    for(int i = 0; i < ysize; ++i)
        m[row][i] *= mult;
}
