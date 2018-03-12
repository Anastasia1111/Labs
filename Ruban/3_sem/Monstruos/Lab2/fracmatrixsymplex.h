#ifndef FRACMATRIXSYMPLEX_H
#define FRACMATRIXSYMPLEX_H

#include "../FracClass/frac.h"
#include <vector>
#include <iostream>

using namespace std;


class FracMatrixSymplex
{
public:
    FracMatrixSymplex(Frac **matrix, int x, int y);
    void rowAdd(int row, Frac *add);
    void rowMulti(int row, Frac mult);
    void colMulti(int col, Frac mult);
    bool setNewSnapshot(); // return false if snapshot was set before
    bool columnIsBasis(int col, int row);
    void symplexMethod();
    bool rebase(int inputColumn, int outputColumn);
    void printMatrix();
    void setBasis(int *columns);
    bool basisWasBefore(int *columns);


private:
    Frac **m;//[xsize][ysize]
    vector<pair<Frac **, int *>> baseSnapshot;
    int xsize;
    int ysize;
    void setBasisInColumn(int column, int row);
    void findOptimal(int &row, int &column);
};

#endif // FRACMATRIXSYMPLEX_H
