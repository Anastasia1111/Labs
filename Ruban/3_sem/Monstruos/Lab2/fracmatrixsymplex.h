#ifndef FRACMATRIXSYMPLEX_H
#define FRACMATRIXSYMPLEX_H

#include "../FracClass/frac.h"
#include <matrixlimitation.h>
#include <vector>
#include <iostream>

using namespace std;


class FracMatrixSymplex
{
public:
    FracMatrixSymplex(Frac **matrix, int x, int y, bool toMin = false);
    FracMatrixSymplex(vector<MatrixLimitation> matrix, MatrixLimitation target);
    void rowAdd(int row, Frac *add);
    void rowMulti(int row, Frac mult);
    void colMulti(int col, Frac mult);
    bool setNewSnapshot(); // return false if snapshot was set before
    int columnIsBasis(int col);
    void symplexMethod();
    bool rebase(int inputColumn, int outputColumn);
    void printMatrix();
    void setBasis(int *columns);
    bool basisWasBefore(int *columns);
    void setZeroInArtif();

private:
    Frac **m;//[xsize][ysize]
    vector<pair<Frac **, int *>> baseSnapshot;
    int xsize;
    int ysize;
    int xmainvar;
    bool toMin;
    void setBasisInColumn(int column, int row);
    void findOptForBasisPlan(int &optimalRow, int &optimalCol);
    void findLeadForBasisPlan(int &leadRow, int &leadCol);
    void rectangleMethod(int optRow, int optColumn);
    bool isOptimal();
};

#endif // FRACMATRIXSYMPLEX_H
