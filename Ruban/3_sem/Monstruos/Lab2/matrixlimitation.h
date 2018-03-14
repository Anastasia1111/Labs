#ifndef MATRIXLIMITATION_H
#define MATRIXLIMITATION_H

#include "../FracClass/frac.h"

class MatrixLimitation
{
public:
    MatrixLimitation(Frac *task, int size, int limit = 0);
    void setLine(Frac *task);
    Frac *getLine();
    void setLimit(int limit);
    int getLimit();

private:
    Frac *line;
    int length;
    int lim;
    /*
     * limit:
     * -1 - eqsmaller || to min
     * 0 - equal
     * 1 - eqbigger || to max
     * */
};

#endif // MATRIXLIMITATION_H
