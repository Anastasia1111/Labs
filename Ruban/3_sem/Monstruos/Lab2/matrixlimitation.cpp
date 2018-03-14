#include "matrixlimitation.h"

MatrixLimitation::MatrixLimitation(Frac *task, int size, int limit) : line(task), length(size), lim(limit)
{

}

void MatrixLimitation::setLine(Frac *task)
{
    line = task;
}

Frac *MatrixLimitation::getLine()
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
