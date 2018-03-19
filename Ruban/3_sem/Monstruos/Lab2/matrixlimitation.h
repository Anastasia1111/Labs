#ifndef MATRIXLIMITATION_H
#define MATRIXLIMITATION_H

#include "../FracClass/frac.h"
#include <vector>

using namespace std;

class MatrixLimitation
{
public:
    MatrixLimitation(vector <Frac> task, int limit = 0);
    void setLine(vector <Frac> task);
    vector <Frac> getLine();
    void setLimit(int limit);
    int getLimit();

private:
    vector <Frac> line; // started from free
    int lim;
    /*
     * limit:
     * -1 - eqsmaller || to min
     * 0 - equal
     * 1 - eqbigger || to max
     * */
};

#endif // MATRIXLIMITATION_H
