#include "matrixlimitation.h"

MatrixLimitation::MatrixLimitation(vector<Frac> task, int limit)
{
    line = task;
    lim = limit;
}

void MatrixLimitation::setLine(vector<Frac> task)
{
    line = task;
}

vector<Frac> MatrixLimitation::getLine()
{
    return line;
}

void MatrixLimitation::setLimit(int limit)
{
    lim = limit;
}

int MatrixLimitation::getLimit()
{
    return lim;
}
